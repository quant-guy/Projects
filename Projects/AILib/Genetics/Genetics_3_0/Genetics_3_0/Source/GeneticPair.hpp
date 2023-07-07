///////////////////////////////////////////////////////////////////////////////////
// COPYRIGHT 2015 Kovach Technologies, Inc.
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the Kovach Technologies, LLC.
// 4. Neither the name of the Kovach Technologies, LLC nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY Kovach Technologies, LLC AS IS AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL Kovach Technologies, LLC BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// AUTHOR : Daniel Kovach
// DATE : 2015-12-30 10:19:06.739857
///////////////////////////////////////////////////////////////////////////////////
#ifndef GENETIC_PAIR_H
#define GENETIC_PAIR_H

#include "Genetics.hpp"

namespace AILib
{

namespace Genetics
{
	//////////////////////////////////////////////////////////////////
	// class structure for the genetic pair representing the atomic
	// unit in the genetic graph 
	//////////////////////////////////////////////////////////////////
	class GeneticPair
	{
		friend ostream & operator << ( ostream & strm, const GeneticPair & p )
		{
			strm << p.GetFirst() << "->" << p.GetSecond() << ';';
			return strm;
		}

		public :

			GeneticPair ( void ) : pair_( 0 ) {}

			GeneticPair ( const unsigned int & _1 ) 
			{
				this->pair_ = new unsigned int ( _1 );
			}

			GeneticPair ( const unsigned int & _1, const unsigned int & _2 )
			{
				this->pair_ = new unsigned int;
				this->SetFirst ( _1 );
				this->SetSecond( _2 );
			}

			GeneticPair ( const GeneticPair & gp )
			{
				this->pair_ = new unsigned int ( * gp.pair_ );
			}

			~GeneticPair ( void ) { if ( this->pair_ ) delete this->pair_; }

			inline const unsigned int GetFirst ( void ) const 
			{ 
				return ( unsigned int ) * ( ( unsigned short * ) pair_ + 0 ); 
			}

			inline const unsigned int GetSecond( void ) const 
			{ 
				return ( unsigned int ) * ( ( unsigned short * ) pair_ + 1 ); 
			}

			inline void SetFirst ( const unsigned int & _1 ) 
			{ 
				* ( ( unsigned short * ) pair_ + 0 ) = ( unsigned short ) _1; 
			}

			inline void SetSecond( const unsigned int & _2 ) 
			{ 
				* ( ( unsigned short * ) pair_ + 1 ) = ( unsigned short ) _2; 
			}

			inline void Swap ( void )
			{
				unsigned int * copy = this->pair_;
				* ( ( ( unsigned short * ) pair_ ) + 1 ) = * ( ( ( unsigned short * ) copy ) + 0 );
				* ( ( ( unsigned short * ) pair_ ) + 0 ) = * ( ( ( unsigned short * ) copy ) + 1 );
			}

		private :

			unsigned int * pair_;
	};


	//////////////////////////////////////////////////////////////////
	// Genetic structure which contains multiple genetic pairs.
	// Genetic operations are built into the genetic graph structure
	// as well as called from within the genetic pair structure
	//////////////////////////////////////////////////////////////////
	class GeneticGraph : virtual public ParentGenetic< GeneticPair * >
	{
		public :

			GeneticGraph( void ) {}

			GeneticGraph( const GeneticGraph & gene ) : ParentGenetic< GeneticPair * >( gene )
			{
				for ( unsigned int i = 0; i < gene.gene_.size(); ++i )
					AddElement( new GeneticPair ( * gene.gene_.at( i ) ) );
				for ( unsigned int i = 0; i < gene.gene_perturbation_functors_.size(); ++i )
					AddFunctor( new PerturbationFunctor( * gene.gene_perturbation_functors_.at( i ) ) );
			}

			GeneticGraph( const char * filename )
			{
				Initialize( filename );
			}

			void Initialize( const char * filename )
			{
				ifstream input( filename, ios::in );
				
				if ( ! input.is_open() )
				{
					cerr << "Error: Unable to open genetic input file: \""
						 << filename << "\"." << endl;
					exit( 1 );
				}

				if ( input.peek() == input.eof() )
				{
					cerr << "Error: File: \""
						 << filename << "\" is empty!" << endl;
					exit( 1 );
				}
				
				const unsigned int MAXLINE = 256;
				char input_line[MAXLINE];
				unsigned int num1 = 0;
				unsigned int num2 = 0;

				// read in file contents, line by line
				while ( input )
				{
					// read in a line of data, break if getline reaches EOF or fails
					if ( ! input.getline(input_line, MAXLINE) )
					{
						break;
					}

					// parse looking for "int->int"
					if ( sscanf( input_line, "%u->%u", &num1, &num2 ) )
					{
						ParentGenetic< GeneticPair * >::AddElement( new GeneticPair( num1, num2 ) );		
					}
				}

				PushFunctors();
				input.close();
			}

			void PushFunctors( void )
			{
				gene_perturbation_functors_.push_back( new Swap() );
				gene_perturbation_functors_.push_back( new SwapBlock() );
				gene_perturbation_functors_.push_back( new Delete() );
				gene_perturbation_functors_.push_back( new SwapElement() );				
				gene_perturbation_functors_.push_back( new ReplaceFirstElement() );				
				gene_perturbation_functors_.push_back( new ReplaceSecondElement() );				
				gene_perturbation_functors_.push_back( new CreateNewElement() );				
			}

			const unsigned int GetLargestElement( void ) const
			{
				unsigned int largest = 0;

				for ( const_genetic_iterator it = this->Begin();
                                      it != this->End();
                                      ++it )
				{
					if ( ( * it )->GetFirst() > largest )
					{
						largest = ( * it )->GetFirst();
					}

					if ( ( * it )->GetSecond() > largest )
					{
						largest = ( * it )->GetSecond();
					}
				} 

				return ++largest;
			}

		public :
			//////////////////////////////////////////////////////////////////
			// Swap elements, where an element is a pair, the first and sec
			// elements being defined by the lower and higher bits of the uint
			// , resp.
			//////////////////////////////////////////////////////////////////
			class SwapElement : virtual public PerturbationFunctor
			{
				public : SwapElement( void ) {}

				public : virtual inline void operator () ( element_vector & elements )  
				{
					( * ( elements.begin() + this->ChooseRandom( elements.size() - 1 ) ) )->Swap();
				}
			};

			//////////////////////////////////////////////////////////////////
			// Replace the first element in the pair.
			//////////////////////////////////////////////////////////////////
			class ReplaceFirstElement : virtual public PerturbationFunctor
			{
				virtual inline void operator () ( element_vector & elements )
				{
					unsigned int temp_random = this->ChooseRandom( elements.size() - 1 );
					unsigned int temp_element_to_replace = this->ChooseRandom( elements.size() - 1 );
					( * ( elements.begin() + temp_random ) )->SetFirst( temp_element_to_replace );
				}
			};

			//////////////////////////////////////////////////////////////////
			// Replace the second element in the pair.
			//////////////////////////////////////////////////////////////////
			class ReplaceSecondElement : public PerturbationFunctor
			{
				virtual inline void operator () ( element_vector & elements )
				{
					unsigned int temp_random = this->ChooseRandom( elements.size() - 1 );
					unsigned int temp_element_to_replace = this->ChooseRandom( elements.size() - 1 );
					( * ( elements.begin() + temp_random ) )->SetSecond( temp_element_to_replace );
				}
			};

			//////////////////////////////////////////////////////////////////
			// Create new element and push it onto the gene
			//////////////////////////////////////////////////////////////////
			class CreateNewElement : public PerturbationFunctor
			{
				virtual inline void operator () ( element_vector & elements )
				{
					unsigned int largest = 0;
					for ( element_vector_iterator it = elements.begin();
					      it != elements.end();
					      ++it )
					{
						if ( ( * it )->GetFirst() > largest )
						{
							largest = ( * it )->GetFirst();
						}

						if ( ( * it )->GetSecond() > largest )
						{
							largest = ( * it )->GetSecond();
						}
					} 

					unsigned int temp_first  = this->ChooseRandom( largest );
					unsigned int temp_second = this->ChooseRandom( largest );
					elements.push_back( new GeneticPair( temp_first, temp_second  ) );
				}
			};
	};

} // Genetics

} // AILib

#endif // GENETIC_PAIR_H
