#!/usr/bin/python

import os
import re
import shutil
import tarfile
from optparse import OptionParser

############################################################################################
# global definitions
############################################################################################
filename_extensions = [ r"\.c$", r"\.cpp$", r"\.h$", r"\.hpp$", r"\.cu$", r"\.py$" ]
unwanted_extensions = [ r"\.a$", r"\.o$", r"\.so$", r"\.swp$", r"\.pyc$", r"~$" ]
json_filename = "graph.json"
dot_filename = "graph.dot"

############################################################################################
# tar a directory
############################################################################################
def targz( output_filename, source_dir ) :
	with tarfile.open( output_filename, "w:gz" ) as tar :
		tar.add( source_dir, arcname = os.path.basename( source_dir ) )

############################################################################################
# loc: determine how many lines of code
############################################################################################
def loc( verbose ) :
	return_value = 0
	for item in os.walk( ".", "*" ) :
		for filename in item[ 2 ] :
			for extension in filename_extensions :
				if re.search( extension, filename ) :
					temp_lines = 0
					with open( item[ 0 ] + '/' + filename, "r" ) as f :
						temp_lines = len( f.readlines() )
					if verbose :
						print "%s/%s, %u" % ( item[ 0 ], filename, temp_lines )
					return_value += temp_lines
	return return_value

############################################################################################
# is_exe: determine if a file is executable or not
############################################################################################
def is_exe( fpath ) :
	return os.path.isfile( fpath ) and os.access( fpath, os.X_OK )

############################################################################################
# remove: remove file, directory, directory tree
############################################################################################
def remove( name ) :
	# try to remove as file
	try :
		os.remove( name )
	except :
		# if not a file, try to remove as directory
		try :
			os.rmdir( name )
		except :
			# if dir not empty, remove dir tree 
			try :
				shutil.rmtree( name )
			except Exception as e :
				pass

############################################################################################
# clean: equivalent of 'make clean'
############################################################################################
def clean( verbose ) :
	if verbose :
		print "Cleaning up cmake files..."
		for item in os.walk( ".", "*" ) :
			if "CMakeFiles" in item[ 0 ] :
				remove( item[ 0 ]   )
			for filename in item[ 2 ] :
				if re.search( r'.*cmake.*', filename.lower() ) :
					if filename != "CMakeLists.txt" :
						remove( item[ 0 ] + '/' + filename )
	if verbose :
		print "Cleaning up Testing directories..."
		for item in os.walk( ".", "*" ) :
			for filename in item[ 2 ] :
				if re.search( r'.*Testing.*', filename ) :
					remove( item[ 0 ] + '/' + filename )
	if verbose :
		print "Cleaning up Makefiles..."
		for item in os.walk( ".", "*" ) :
			for filename in item[ 2 ] :
				if re.search( r'Makefile', filename ) :
					remove( item[ 0 ] + '/' + filename )
	if verbose :
		print "Cleaning up .o, .so, .a, .swp, .pyc, .*~, and executable files..."
		for item in os.walk( ".", "*" ) :
			for filename in item[ 2 ] :
				for unwanted in unwanted_extensions :
					if re.search( unwanted, filename ) :
						remove( item[ 0 ] + '/' + filename )
					if is_exe( item[ 0 ] + '/' + filename ) :
						if not re.search( r'py$|sh$', filename ) :
							remove( item[ 0 ] + '/' + filename )

############################################################################################
# code_graph: create graph of code, output json object for html rendering
############################################################################################
def code_graph() :
	nodes = []
	relationships = []
	for item in os.walk( ".", "*" ) :
		for filename in item[ 2 ] :
			for extension in filename_extensions :
				if re.search( extension, filename ) :
					nodes.append( [ item[ 0 ] + '/' + filename, filename ] )

	for item in os.walk( ".", "*" ) :
		for filename in item[ 2 ] :
			for extension in filename_extensions :
				if re.search( extension, filename ) :
					with open( item[ 0 ] + '/' + filename, "r" ) as f :
						for line in f.readlines() :
							if "#include" in line :
								for node in nodes :
									if node[ 1 ] in line :
										src = nodes.index( [ item[ 0 ] + '/' + filename, filename ] )
										dest = nodes.index( node )
										relationships.append( [ src, dest ] )

	with open( json_filename, "a" ) as f :
		f.write( "{\n" )
		f.write( "\"nodes\":[\n" )
		for i in nodes :
			if i != nodes[ -1 ] :
				f.write( "{\"name\"=\"%s\",\"group\"=1},\n" % i[ 0 ] )
			else :
				f.write( "{\"name\"=\"%s\",\"group\"=1}\n" % i[ 0 ] )
		f.write( "],\n" )
		f.write( "\"list\":[" )
		for i in relationships :
			if i != relationships[ -1 ] :
				f.write( "{\"source\"=%u,\"target\"=%u,\"relationship\"=\"includes\"},\n" % ( i[ 0 ], i[ 1 ] ) )
			else :
				f.write( "{\"source\"=%u,\"target\"=%u,\"relationship\"=\"includes\"}\n" % ( i[ 0 ], i[ 1 ] ) )
		f.write( "]\n" )
		f.write( "}\n" )

############################################################################################
# main: where the magic happens
############################################################################################
if __name__ == "__main__" :

	############################################################################################
	# command line parsing options
	############################################################################################
	parser = OptionParser()
	parser.add_option( "-g", "--Graph", dest = "graph", action = "store_true", default = False, help = "Form node edge graph of code base." )
	parser.add_option( "-c", "--Clean", dest = "clean", action = "store_true", default = False, help = "Equivalent of \"make clean\"" )
	parser.add_option( "-l", "--LOC", dest = "loc", action = "store_true", default = False, help = "Lines of code" )
	parser.add_option( "-t", "--Tar", dest = "tar", action = "store_true", default = False, help = "Create .tar.gz of Projects" )
	parser.add_option( "-v", "--Verbose", dest = "verbose", action = "store_true", default = False, help = "Verbose mode" )

	( options, args ) = parser.parse_args() 


	############################################################################################
	# main implementation
	############################################################################################
	if options.graph :
		clean( False )
		code_graph()
							
	if options.clean : 
		clean( True )

	if options.loc :
		clean( False )
		code_lines = 0
		if options.verbose :
			code_lines = loc( True )
		else :
			code_lines = loc( False )
		print "Lines of code: %u" % code_lines

	if options.tar :
		print "Creating .tar.gz of Projects..."
		clean( False )
		targz( "../Projects.tar.gz", "../Projects" )
