/*
The MIT License (MIT)

	Copyright (c) 2015 nsweb

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "Eigen/Dense"

// Change these values to your needs
#define WITH_KSVD_DOUBLE	0
#define WITH_KSVD_STDVECTOR 1

#if WITH_KSVD_STDVECTOR
	#include <vector>
	#define ARRAY_T(T)				std::vector<T>
	#define PUSH_ARRAY_T(a, val)	(a).push_back(val)
	#define SIZE_ARRAY_T(a)			((int)(a).size())
#endif

/**/
namespace ksvd
{
#if WITH_KSVD_DOUBLE
	typedef double Scalar_t;
#else
	typedef float Scalar_t;
#endif

	typedef Eigen::Matrix<Scalar_t, Eigen::Dynamic, Eigen::Dynamic>						Matrix_t;
	typedef Eigen::Matrix<Scalar_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>	MatrixRowMajor_t;
	typedef Eigen::Matrix<Scalar_t, 1, Eigen::Dynamic >									RowVector_t;
	typedef Eigen::Matrix<Scalar_t, Eigen::Dynamic, 1>									Vector_t;

	class Solver
	{
	public:
		Solver();
		~Solver();
		
		void Init( int _target_sparcity, int _dictionary_size, int _dimensionality, int _sample_count, bool _bVerbose );
		void KSVDStep( int kth );
		void OMPStep();
		void BatchOMPStep();

		/** The dictionary - nb of rows = dimensionality - nb of cols = number of atoms / dictionary size */
		Matrix_t Dict;
		/** The encoded samples - nb of rows = number of atoms / dictionary size - nb of cols = number of samples */
		Matrix_t X;
		/** The original samples - nb of rows = dimensionality - nb of cols = number of initial samples */
		Matrix_t Y;

		int target_sparcity;
		int dictionary_size;
		int dimensionality;
		int sample_count;
		bool bVerbose;
	};

	void TestSolver();
	void SolveImg( Scalar_t* img_data, int with, int height, Scalar_t* out_data/*, Scalar_t* out_atoms, int* width_atoms, int* height_atoms*/ );


}; /*namespace ksvd*/