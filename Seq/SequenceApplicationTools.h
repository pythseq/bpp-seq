//
// File: SequenceApplicationTools.h
// Created by: Julien Dutheil
// Created on: Fri Oct 21 13:13
// from file old ApplicationTools.h created on Sun Dec 14 09:36:26 2003
//

/*
Copyright or � or Copr. CNRS, (November 17, 2004)

This software is a computer program whose purpose is to provide classes
for sequences analysis.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#ifndef _SEQUENCEAPPLICATIONTOOLS_H_
#define _SEQUENCEAPPLICATIONTOOLS_H_

#include "alphabets"
#include "containers"

/**
 * @brief This class provides some common tools for applications.
 *
 * The functions parse some option file, create corresponding objects and send
 * a pointer toward it.
 * 
 * The option files are supposed to follow this simple format:<br />
 * <code>parameterName = parameterContent</code><br />
 * with one parameter per line.
 *
 * In files, shell comments: <code> # my comment line here </code>,
 * C comments: <code> / * my comment block here * / </code>
 * and C++ comments: <code> // my comment line here </code> are allowed, and ignored while parsing.
 */
class SequenceApplicationTools
{
	public:
		SequenceApplicationTools() {}
		virtual ~SequenceApplicationTools() {}
		
	public:
		/**
		 * @brief Build an Alphabet object according to options.
		 *
		 * Options used are:
		 * - alphabet = [DNA|RNA|Protein], the alphabet type to use.
		 *
		 * @param params  The attribute map where options may be found.
		 * @param suffix  A suffix to be applied to each attribute name.
		 * @param suffixIsOptional Tell if the suffix is absolutely required.
		 * @param verbose Print some info to the 'message' output stream.
		 * @return A new Alphabet object according to options specified.
		 */
		static Alphabet * getAlphabet(
			map<string, string> & params,
			const string & suffix = "",
			bool suffixIsOptional = true,
			bool verbose = true);
		
		/**
		 * @brief Build a SequenceContainer object according to options.
		 *
		 * Options used are:
		 * - sequence.format = [Fasta|Mase|Phylip|Clustal|DCSE], the format of the sequence file.
		 * - sequence.file = file_path, the path of the file to parse.
		 * Options depending on other options:
		 * - If Phylip format is to be used:
		 *   - sequence.format_phylip.order = [interleaved|sequential].
		 *   - sequence.format_phylip.ext   = [classic|extended].
		 * - If Mase format is to be used:
		 *   - sequence.format_mase.site_selection = name of the selection.
		 *
		 * @param alpha   The alphabet to use in the container.
		 * @param params  The attribute map where options may be found.
		 * @param suffix  A suffix to be applied to each attribute name.
		 * @param suffixIsOptional Tell if the suffix is absolutely required.
		 * @param verbose Print some info to the 'message' output stream.
		 * @return A new VectorSiteContainer object according to options specified.
		 */
		static VectorSiteContainer * getSiteContainer(
			const Alphabet * alpha,
			map<string, string> & params,
			const string & suffix = "",
			bool suffixIsOptional = true,
			bool verbose = true);
			
		/**
		 * @brief Retrieves sites suitable for the analysis.
		 *
		 * Options used are:
		 * - sequence.sites_to_use = [complete|nogap].
		 *
		 * If the 'complete' option is used, only fully resolve site will be taken
		 * into account.
		 * If the 'nogap' option is used, only sites without gap will be taken into
		 * account.
		 *
		 * @param allSites The site container from which sites must be retrieved.
		 * @param params   The attribute map where options may be found.
		 * @param suffix   A suffix to be applied to each attribute name.
		 * @param suffixIsOptional Tell if the suffix is absolutely required.
		 * @param verbose Print some info to the 'message' output stream.
		 * @return A new VectorSiteContainer object containing sites of interest.
		 */
		static VectorSiteContainer * getSitesToAnalyse(
			const SiteContainer & allSites,
			map<string, string> & params,
			string suffix = "",
			bool suffixIsOptional = true,
			bool verbose = true);

		/**
		 * @brief Write a sequence file according to options.
		 *
		 * Optioins used are:
		 * - output.sequence.format = [Fasta|Mase|Phylip], the format of the sequence file.
		 * - output.sequence.file = file_path, the path of the file to parse.
		 * - output.sequence.length = the max number of chars on a line.
		 * Options depending on other options:
		 * - If Phylip format is to be used:
		 *   - output.sequence.format_phylip.order = [interleaved|sequential].
		 *   - output.sequence.format_phylip.ext   = [classic|extended].
		 *
		 * @param sequences The sequences to write.
		 * @param params  The attribute map where options may be found.
		 * @param suffix  A suffix to be applied to each attribute name.
		 * @param verbose Print some info to the 'message' output stream.
		 */
		static void writeSequenceFile(
			const SequenceContainer & sequences,
			map<string, string> & params,
			const string & suffix = "",
			bool verbose = true);
};

#endif //_SEQUENCEAPPLICATIONTOOLS_H_

