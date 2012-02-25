var FileSystem = require( 'fs' );

////////////////////////////////////////////////

function Namespace( parent, parameter ) {
	
	this.parent = parent;
	
	this.name = parameter;
	
	try { FileSystem.statSync( parameter ); }
	catch ( e ) { FileSystem.mkdirSync( parameter, 0755 ); }
	
	process.chdir( parameter );
	
}

Namespace.prototype.close = function ( ) {
	
	process.chdir( '..' );
	
};

////////////////////////////////////////////////

function Class( parent, parameter ) {
	
	this.parent = parent;
	
	this.infos = parameter.split( / +: +/ );
	
	this.fd = FileSystem.openSync( this.infos[ 0 ] + '.hh', 'w', 0644 );
	
	this.headers.list = [ ];
	
	this.definitions.list = [ ];
	
	this.enumerations = Object.create( null );
	
}

Class.prototype.headers = function ( ) {
	
	var buffer = '';
	
	this.headers.list.forEach( function ( header, index ) {
		
		if ( index ) buffer += '\n';
		
		buffer += '#include ' + header;
		
	} );
	
	return buffer;
	
};

Class.prototype.definitions = function ( ) {
	
	var buffer = '';
	
	this.definitions.list.forEach( function ( definition, index ) {
		
		if ( index ) buffer += '\n\n';
		
		buffer += definition[ 0 ] + ' ' + definition[ 1 ] + ';';
		
	} );
	
	return buffer;
	
};

Class.prototype.write = function ( str ) {
	
	str.split( /\n/g ).forEach( function ( line, index ) {
		
		FileSystem.writeSync( this.fd, this.indentation + line + '\n', null );
		
	}, this );
	
};

Class.prototype.close = function ( ) {
	
	this.indentation = '';
	
	this.write( '#pragma once' );
	this.write( '' );
	
	var headers = this.headers( );
	
	if ( headers ) {
		
		this.write( headers );
		this.write( '' );
		
	}
	
	var nsRecurse = function ( ns ) {
		
		if ( ! ns ) return ;
		
		nsRecurse( ns.parent );
		
		this.write( 'namespace ' + ns.name );
		this.write( '{' );
		
		this.indentation += '\t';
		
		this.write( '' );
		
	}.bind( this );
	
	nsRecurse( this.parent );
	
	var declaration = 'struct ' + this.infos[ 0 ];
	if ( this.infos[ 1 ] ) declaration += ' : public ' + this.infos[ 1 ];
	
	this.write( declaration + ' {' );
	
	Object.keys( this.enumerations ).forEach( function ( name ) {
		
		this.write( 'enum ' + name + ' {' );
		
		this.indentation += '\t';
		
		var elements = this.enumerations[ name ];
		
		elements.forEach( function ( element, index ) {
			
			this.write( element + ( index + 1 === elements.length ? '' : ',' ) );
			
		}, this );
		
		this.indentation = this.indentation.substr( 1 );
		
		this.write( '};' );
		
	}, this );
	
	this.indentation += '\t';
	this.write( '' );
	this.write( 'virtual ~' + this.infos[ 0 ] + '( void ) { }' );
	this.write( '' );
	this.write( this.definitions( ) );
	this.write( '' );
	this.indentation = this.indentation.substr( 1 );
	
	this.write( '};' );
	
	while ( this.indentation.length ) {
		
		this.write( '' );
		
		this.indentation = this.indentation.substr( 1 );
		
		this.write( '}' );
		
	}
	
	FileSystem.close( this.fd );
	
};

////////////////////////////////////////////////

function Header( parent, parameter ) {
	
	parent.headers.list.push( parameter );
	
}

Header.prototype.close = function ( ) {
	
};

////////////////////////////////////////////////

function Property( parent, parameter ) {
	
	var infos = parameter.split( / +: +/ );
	
	parent.definitions.list.push( [ infos[ 1 ], infos[ 0 ] ] );
	
}

Property.prototype.close = function ( ) {
	
};

////////////////////////////////////////////////

function Enumeration( parent, parameter ) {
	
	this.elements = parent.enumerations[ parameter ] = [ ];
	
}

Enumeration.prototype.close = function ( ) {
	
};

////////////////////////////////////////////////

function Element( parent, parameter ) {
	
	parent.elements.push( parameter );
	
}

Element.prototype.close = function ( ) {
	
};

////////////////////////////////////////////////

var Symbols = { };

Symbols[ '=' ] = Namespace;
Symbols[ '@' ] = Class;
Symbols[ '#' ] = Header;
Symbols[ '+' ] = Property;
Symbols[ '~' ] = Enumeration;
Symbols[ '-' ] = Element;

////////////////////////////////////////////////

var stack = [ ];

FileSystem.readFileSync( process.argv[ 2 ], 'utf-8' ).split( /\n/g ).forEach( function ( line ) {
	
	var infos = line.match( /^( *)(.) (.*)$/ );
	
	if ( ! infos )
		
		return ;
	
	infos.shift( );
	
	var depth = infos[ 0 ].length / 2;
	
	while ( stack.length && stack[ 0 ].depth >= depth ) {
		
		stack[ 0 ].close( );
		
		stack.shift( );
		
	}
	
	var action = new ( Symbols[ infos[ 1 ] ] )( stack[ 0 ], infos[ 2 ] );
	
	action.depth = depth;
	
	stack.unshift( action );
	
} );
