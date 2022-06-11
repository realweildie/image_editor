#pragma once
#include <iostream>

namespace math
{
	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	template<typename T, int P, int Q>
	struct MasWrapper2
	{
		T mas[P][Q];
	};

	template<typename T, int N, int M>
	class Matrix
	{
	public:
		Matrix()
		{
			_n = N;
			_m = M;
			for (int i = 0; i < _n; i++)
				for (int j = 0; j < _m; j++)
					_mat[i][j] = 0;
		}

		Matrix(const T mas[N][M])
		{
			_n = N;
			_m = M;
			for (int i = 0; i < _n; i++)
				for (int j = 0; j < _m; j++)
					_mat[i][j] = mas[i][j];
		}

		Matrix(const MasWrapper<T, N, M>& mas)
		{
			_n = N;
			_m = M;
			for (int i = 0; i < _n; i++)
				for (int j = 0; j < _m; j++)
					_mat[i][j] = mas.mas[i][j];
		}

		Matrix(const Matrix<T, N, M>& mat)
		{
			_n = mat._n;
			_m = mat._m;
			for (int i = 0; i < _n; i++)
				for (int j = 0; j < _m; j++)
					_mat[i][j] = mat._mat[i][j];
		}

		int getWidth() const { return _n; }
		int getHeight() const { return _m; }
		T get(int i, int j) const { return _mat[i][j]; }
		void set(int i, int j, T data) { _mat[i][j] = data; }

		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
			_n = mat.getN();
			_m = mat.getM();

			for (int i = 0; i < _n; i++)
				for (int j = 0; j < _m; j++)
					_mat[i][j] = mat.get(i, j);

			return *this;
		}

		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
			Matrix<T, N, M> tmp;
			for (int i = 0; i < _n; i++)
				for (int j = 0; j < _m; j++)
					tmp._mat[i][j] = _mat[i][j] + mat._mat[i][j];
			return tmp;
		}

		template<typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
			Matrix<T, N, M> tmp;
			for (int i = 0; i < _n; i++)
				for (int j = 0; j < _m; j++)
					tmp._mat[i][j] = _mat[i][j] - mat._mat[i][j];
			return tmp;
		}

		template<typename T, int P, int Q>
		Matrix<T, N, Q> operator*(const Matrix<T, P, Q>& mat)
		{
			Matrix<T, N, Q> tmp;
			if (M == P)
			{
				for (int i = 0; i < _n; i++)
					for (int j = 0; j < mat.getM(); j++)
					{
						T sum = 0;
						for (int k = 0; k < _m; k++)
							sum += _mat[i][k] * mat.get(k, j);
						tmp.set(i, j, sum);
					}
			}
			else {
				throw std::exception("Wrong matrix size!");
			}
			return tmp;
		}

		T determinant()
		{
			T result = 0;

			if (_n == 2 && _m == 2)
			{
				result = _mat[0][0] * _mat[1][1] -
						 _mat[0][1] * _mat[1][0];
			}
			else if (_n == 3 && _m == 3)
			{
				result = _mat[0][0] * _mat[1][1] * _mat[2][2] - _mat[0][0] * _mat[1][2] * _mat[2][1]
					   - _mat[0][1] * _mat[1][0] * _mat[2][2] + _mat[0][1] * _mat[1][2] * _mat[2][0]
					   + _mat[0][2] * _mat[1][0] * _mat[2][1] - _mat[0][2] * _mat[1][1] * _mat[2][0];
			}
			else
			{
				throw std::exception("Wrong matrix!");
			}

			return result;
		}

		Matrix<T, N, M> transpose()
		{
			Matrix<T, N, M> tmp;

			for (int i = 0; i < _n; i++)
			{
				for (int j = 0; j < _m; j++)
				{
					tmp.set(i, j, _mat[j][i]);
				}
			}

			return tmp;
		}

		~Matrix() {}

		template<typename T, int N, int M>
		friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);

		template<typename T, int N, int M>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

	private:
		int _n, _m;
		T _mat[N][M];
	};

	template<typename T, int N, int M>
	std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat._n; i++)
			for (int j = 0; j < mat._m; j++)
				in >> mat._mat[i][j];
		return in;
	}

	template<typename T, int N, int M>
	std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat._n << "x" << mat._m << std::endl;
		for (int i = 0; i < mat._n; i++) {
			for (int j = 0; j < mat._m; j++)
				out << mat._mat[i][j] << " ";
			out << std::endl;
		}
		return out;
	}

	using Vec2i = Matrix<int, 2, 1>;
	using Vec2d = Matrix<double, 2, 1>;
	using Mat22i = Matrix<int, 2, 2>;
	using Mat22d = Matrix<double, 2, 2>;
}