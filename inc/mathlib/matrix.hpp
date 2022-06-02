#pragma once
#include <iostream>
#include <cmath>

namespace math
{
		// MY_DEBUG 
		//#define MY_DEBUG 

		template<typename T, int N, int M>
		struct MasWrapper
		{
			T mas[N][M];
		};

		template<typename T, int N, int M>
		class Matrix
		{
		public:
			// Constructor
			Matrix()
			{
	#ifdef MY_DEBUG
				std::cout << "Constructor matrix with zero elements" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = 0;
			}

			// Constructor
			Matrix(const T mas[N][M])
			{
	#ifdef MY_DEBUG
				std::cout << "First constructor matrix-template with no-zero elements" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mas[i][j];
			}

			// Constructor
			Matrix(const MasWrapper<T, N, M>& mas)
			{
	#ifdef MY_DEBUG
				std::cout << "Second constructor matrix-template with no-zero elements" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mas.mas[i][j];
			}

			// Copy constructor
			Matrix(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "Copy constructor" << std::endl;
	#endif

				m_n = mat.m_n;
				m_m = mat.m_m;

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mat.m_mat[i][j];
			}

			int getN() const { return m_n; }
			int getM() const { return m_m; }
			T get(int i, int j) const { return m_mat[i][j]; }
			void set(int i, int j, T data) { m_mat[i][j] = data; }

			// Operator assignment 
			template<typename T, int N, int M>
			Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "Operator =" << std::endl;
	#endif

				m_n = mat.getN();
				m_m = mat.getM();

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mat.get(i, j);
				return *this;
			}

			// Addition operator
			template<typename T, int N, int M>
			Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "operator+" << std::endl;
	#endif
				Matrix<T, N, M> tmp;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
				return tmp;
			}

			// Task 1: Subtraction operator with a template
			template<typename T, int N, int M>
			Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
			{
#ifdef MY_DEBUG
				std::cout << "operator-" << std::endl;
#endif
				Matrix<T, N, M> tmp;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
				return tmp;
			}


			// Task 2: Multiplication operator with a template
			template<typename T, int N, int M>
			Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "operator*" << std::endl;
	#endif
				Matrix<T, N, M> tmp;

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < mat.getM(); j++)
					{
						T sum = 0;
						for (int k = 0; k < m_m; k++)
							sum += m_mat[i][k] * mat.get(k, j);
						tmp.set(i, j, sum);
					}

				return tmp;
			}

			// Task 3: Matrix determinant operator with a template (via the get method)
			T determinant()
			{
				T result = -1;
				if ((this->getM() != this->getN())) {
					std::cout << "The matrix is not square. The operation is not supported." << std::endl;
					return result;
				}
				else {
					if ((this->getM() > 3)) {
						std::cout << "The matrix is square, but " << m_n << "x" << m_m << std::endl;
						std::cout << "The operation is not supported, because ">3"." << std::endl;
						return result;
					}

					if ((this->getM()== 2)) {
						std::cout << "The matrix is square. The operation is supported." << std::endl;
						result = this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0);
						return result;
					}
					
					if ((this->getM() == 3)) {
						std::cout << "The matrix is square. The operation is supported." << std::endl;
						result = this->get(0, 0) * this->get(1, 1) * this->get(2, 2) +
							this->get(1, 0) * this->get(2, 1) * this->get(0, 2) +
							this->get(2, 0) * this->get(0, 1) * this->get(1, 2) -
							this->get(2, 0) * this->get(1, 1) * this->get(0, 2) -
							this->get(1, 0) * this->get(0, 1) * this->get(2, 2) -
							this->get(0, 0) * this->get(2, 1) * this->get(1, 2);
						return result;
					}
					return result;
				}
			}
			// Task 4: Transpose operator with template (without get method)
			Matrix<T, N, M> transpose() {
				Matrix<T, N, M> tmp;
				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						tmp.m_mat[i][j] = m_mat[j][i];
				return tmp;
			}

			// Task 5: Inverse matrix with a template
			Matrix<T, N, M> inverse()
			{
				float reverse = determinant();
				Matrix<T, N, M> tmp;
				std::cout<<"before tmp is: "<<tmp<<std::endl;
				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						tmp.m_mat[i][j] = m_mat[i][j];
				std::cout<<"after tmp is: "<<tmp<<std::endl;

				if (this->getM() == this->getN()) {
					if (reverse == 0)
					{
						std::cout << "The determinant is zero. The matrix is degenerate." << std::endl;
						std::cout << "She doesn't have a reverse. The operation is not supported." << std::endl;
						return -1;
					}
					else
					{
						std::cout << "The determinant is not zero. The matrix is generate. She have a reverse." << std::endl;
						if (this->getM() == 2)
						{
							tmp.m_mat[0][0] = m_mat[1][1] / reverse;
							tmp.m_mat[0][1] = -m_mat[0][1] / reverse;
							tmp.m_mat[1][0] = -m_mat[1][0] / reverse;
							tmp.m_mat[1][1] = m_mat[0][0] / reverse;
							return tmp;
						}
						if (this->getM() == 3)
						{
							tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / reverse;
							tmp.m_mat[1][0] = -(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / reverse;
							tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / reverse;
							tmp.m_mat[0][1] = -(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / reverse;
							tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / reverse;
							tmp.m_mat[2][1] = -(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / reverse;
							tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / reverse;
							tmp.m_mat[1][2] = -(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / reverse;
							tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / reverse;
							return tmp;
						}

						if ((this->getM() > 3)) {
							std::cout << "The operation is not supported for higher order matrixes." << std::endl;
							return -1;
						}
					}
				}
				else {
					std::cout << "This operation is only available for square matrixes." << std::endl;
					return -1;
				}
			}
			// Destructor
			~Matrix()
			{
	#ifdef MY_DEBUG
				std::cout << "Destructor" << std::endl;
	#endif
			}
			// friend - allows the function to have access to private fields/methods of the class
			template<typename T, int N, int M>
			friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);

			template<typename T, int N, int M>
			friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

		private:
			int m_n, m_m;
			T m_mat[N][M];
		};

		// Overloading the input operator
		template<typename T, int N, int M>
		std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
		{
			for (int i = 0; i < mat.m_n; i++)
				for (int j = 0; j < mat.m_m; j++)
					in >> mat.m_mat[i][j];
			return in;
		}

		// Overloading the output operator
		template<typename T, int N, int M>
		std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
		{
			out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
			for (int i = 0; i < mat.m_n; i++) {
				for (int j = 0; j < mat.m_m; j++)
					out << mat.m_mat[i][j] << " ";
				out << std::endl;
			}
			return out;
		}

		using Vec2i = Matrix<int, 2, 1>;// Abbreviated convenient name
		using Vec2d = Matrix<double, 2, 1>;
		using Mat22i = Matrix<int, 2, 2>;
		using Mat22d = Matrix<double, 2, 2>;
		using Mat33i = Matrix<int, 3, 3>;
		using Mat33d = Matrix<double, 3, 3>;
		//adding to check the operation of the operators

}
void introduction() {
	std::cout << "Welcome to the math library! Please, check some tests!" << std::endl;
}
void ending() {
	std::cout << "The program has finished working out!" << std::endl;
}