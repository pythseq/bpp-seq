//
// File: StandardGeneticCode.h
// Created by: jdutheil <Julien.Dutheil@univ-montp2.fr>
// Created on: Mon Oct 13 15:39:17 2003
//

#include "StandardGeneticCode.h"
#include "StandardCodonAlphabet.h"
#include "ProteicAlphabet.h"
#include <iostream>

StandardGeneticCode::StandardGeneticCode(const NucleicAlphabet * alpha) : GeneticCode() 
{
	codonAlphabet   = new StandardCodonAlphabet(alpha);
	proteicAlphabet = new ProteicAlphabet();
}


StandardGeneticCode::~StandardGeneticCode() {
	delete codonAlphabet;
	delete proteicAlphabet;	
}

int    StandardGeneticCode::translate(      int i     ) const throw (BadIntException) {
	vector<int> positions = codonAlphabet -> getPositions(i);
	switch(positions[0]) {
		//First position:
		case 0 : //A
		switch(positions[1]) {
			//Second position:
			case 0 : //AA
			switch(positions[2]) {
				//Third position:
				case 0 : case 2 :          return proteicAlphabet -> charToInt("K"); //Lysine
				case 1 : case 3 :          return proteicAlphabet -> charToInt("N"); //Asparagine
			}
			case 1 : //AC
			                               return proteicAlphabet -> charToInt("T"); //Threonine
			case 2 : //AG
			switch(positions[2]) {
				//Third position:
				case 0 : case 2 :          return proteicAlphabet -> charToInt("R"); //Arginine
				case 1 : case 3 :          return proteicAlphabet -> charToInt("S"); //Serine
			}
			case 3 : //AT
			switch(positions[2]) {
				//Third position:
				case 2:                    return proteicAlphabet -> charToInt("M"); //Methionine
				case 0 : case 1 : case 3 : return proteicAlphabet -> charToInt("I"); //Isoleucine
			}
		}
		case 1 : //C
		switch(positions[1]) {
			//Second position:
			case 0 : //CA
			switch(positions[2]) {
				//Third position:
				case 0 : case 2 :          return proteicAlphabet -> charToInt("Q"); //Glutamine
				case 1 : case 3 :          return proteicAlphabet -> charToInt("H"); //Histidine
			}
			case 1 : //CC
			                               return proteicAlphabet -> charToInt("P"); //Proline
			case 2 : //CG
			                               return proteicAlphabet -> charToInt("R"); //Arginine
			case 3 : //CT
			                               return proteicAlphabet -> charToInt("L"); //Leucine
		}
		case 2 : //G
		switch(positions[1]) {
			//Second position:
			case 0 : //GA
			switch(positions[2]) {
				//Third position:
				case 0 : case 2 :          return proteicAlphabet -> charToInt("E"); //Glutamic acid
				case 1 : case 3 :          return proteicAlphabet -> charToInt("D"); //Aspartic acid
			}
			case 1 : //GC
			                               return proteicAlphabet -> charToInt("A"); //Alanine
			case 2 : //GG
			                               return proteicAlphabet -> charToInt("G"); //Glycine
			case 3 : //GT
			                               return proteicAlphabet -> charToInt("V"); //Valine
		}
		case 3 : //T(U)
		switch(positions[1]) {
			//Second position:
			case 0 : //TA
			switch(positions[2]) {
				//Third position:
				case 0 :                   throw StopCodonException("", "TAA"); //Stop codon
				case 2 :                   throw StopCodonException("", "TAG"); //Stop codon
				case 1 : case 3 :          return proteicAlphabet -> charToInt("Y"); //Tyrosine
			}
			case 1 : //TC
			                               return proteicAlphabet -> charToInt("S"); //Serine
			case 2 : //TG
			switch(positions[2]) {
				//Third position:
				case 0 :                   throw StopCodonException("", "TGA"); //Stop codon
				case 2 :                   return proteicAlphabet -> charToInt("W"); //Tryptophane
				case 1 : case 3 :          return proteicAlphabet -> charToInt("C"); //Cysteine
			}
			case 3 : //TT
			switch(positions[2]) {
				//Third position:
				case 0 : case 2 :          return proteicAlphabet -> charToInt("L"); //Leucine
				case 1 : case 3 :          return proteicAlphabet -> charToInt("F"); //Phenylalanine
			}
		}
	}
	throw BadIntException(i, "StandardGeneticCode::translate", codonAlphabet);
}

string StandardGeneticCode::translate(const string & c) const throw (BadCharException) {
	return proteicAlphabet -> intToChar(translate(codonAlphabet -> charToInt(c)));
}
