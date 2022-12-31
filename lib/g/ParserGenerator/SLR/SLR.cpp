//
//	g/ParserGenerator/SLR.cpp
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/SLR/SLR.h"

namespace G {
namespace ParserGenerator {

//
//  Generate.SLR.Items( ) =  Generate.LR0.Items( )
//
//  Generate.SLR.Reductions( ) =
//  	R <- {}
//  	for each state I in T
//  		for each item A -> a• in I
//  			for each token X in FOLLOW( A)
//  				R <- R U {( I, X, A -> a)}
//

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/SLR.cpp
