#include <stdlib.h>
#include <time.h>

typedef double	t_flt;

typedef struct t_m4x4
{
	t_flt	_[4][4];
}			t_m4x4;

void	multiply_m4x4_by_reference(t_m4x4 *dest, t_m4x4 const *mult, t_m4x4 const *m4x4)
{
	size_t	m;

	m = -1;
	while (++m < 4)
	{
		dest->_[m][00] = mult->_[m][0] * m4x4->_[0][0];
		dest->_[m][0] += mult->_[m][1] * m4x4->_[1][0];
		dest->_[m][0] += mult->_[m][2] * m4x4->_[2][0];
		dest->_[m][0] += mult->_[m][3] * m4x4->_[3][0];
		dest->_[m][01] = mult->_[m][0] * m4x4->_[0][1];
		dest->_[m][1] += mult->_[m][1] * m4x4->_[1][1];
		dest->_[m][1] += mult->_[m][2] * m4x4->_[2][1];
		dest->_[m][1] += mult->_[m][3] * m4x4->_[3][1];
		dest->_[m][02] = mult->_[m][0] * m4x4->_[0][2];
		dest->_[m][2] += mult->_[m][1] * m4x4->_[1][2];
		dest->_[m][2] += mult->_[m][2] * m4x4->_[2][2];
		dest->_[m][2] += mult->_[m][3] * m4x4->_[3][2];
		dest->_[m][03] = mult->_[m][0] * m4x4->_[0][3];
		dest->_[m][3] += mult->_[m][1] * m4x4->_[1][3];
		dest->_[m][3] += mult->_[m][2] * m4x4->_[2][3];
		dest->_[m][3] += mult->_[m][3] * m4x4->_[3][3];
	}
}

t_m4x4	multiply_m4x4_by_value(t_m4x4 mult, t_m4x4 m4x4)
{
	t_m4x4	res;
	size_t	m;

	m = -1;
	while (++m < 4)
	{
		res._[m][00] = mult._[m][0] * m4x4._[0][0];
		res._[m][0] += mult._[m][1] * m4x4._[1][0];
		res._[m][0] += mult._[m][2] * m4x4._[2][0];
		res._[m][0] += mult._[m][3] * m4x4._[3][0];
		res._[m][01] = mult._[m][0] * m4x4._[0][1];
		res._[m][1] += mult._[m][1] * m4x4._[1][1];
		res._[m][1] += mult._[m][2] * m4x4._[2][1];
		res._[m][1] += mult._[m][3] * m4x4._[3][1];
		res._[m][02] = mult._[m][0] * m4x4._[0][2];
		res._[m][2] += mult._[m][1] * m4x4._[1][2];
		res._[m][2] += mult._[m][2] * m4x4._[2][2];
		res._[m][2] += mult._[m][3] * m4x4._[3][2];
		res._[m][03] = mult._[m][0] * m4x4._[0][3];
		res._[m][3] += mult._[m][1] * m4x4._[1][3];
		res._[m][3] += mult._[m][2] * m4x4._[2][3];
		res._[m][3] += mult._[m][3] * m4x4._[3][3];
	}
	return (res);
}

t_m4x4	random_matrix(void)
{
	t_m4x4	random;

	for (size_t i = 0; i < 16; ++i)
		random._[i / 4][i % 4] = rand();
	return (random);
}

int	main(void)
{
	srand(time(NULL));
	t_m4x4	result;
	t_m4x4	m1;
	t_m4x4	m2;
	for (size_t i = 0; i < 80000000; ++i)
	{
		m1 = random_matrix();
		m2 = random_matrix();
		// multiply_m4x4_by_reference(&result, &m1, &m2);
		result = multiply_m4x4_by_value(m1, m2);
	}
	return (0);
}
