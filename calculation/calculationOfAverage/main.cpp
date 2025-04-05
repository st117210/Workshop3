#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

const double H = 0.272;
const double V_0 = 1.050;
const double omega_h = 0.001;
const double omega_v_0 = 0.005;

std::vector<double> delta_T(const std::vector<std::vector<double>>& data, std::vector<double>& avarage)
{
	std::vector<double> delta_t(6, 0);
	for (int i = 1; i < 7; ++i)
	{
		double sum = 0.0;
		for (int j = 0; j < 29; ++j)
		{
			double d = (data[j][i] - avarage[i - 1]);
			sum += d * d;
		}
		delta_t[i - 1] = sqrt((sum) / (data.size()));
		delta_t[i - 1] /= sqrt(30);
	}

	return delta_t;
}

std::vector<double> g(std::vector<double>& avarage)
{
	std::vector<double> arr(6, 0);
	for (int i = 0; i < 6; i++)
	{
		double t_i = avarage[i] / 1000;
		arr[i] = 2 * (H - V_0 * t_i) / (t_i * t_i);
	}

	return arr;
}

std::vector<double> delta_g(std::vector<double>& avarage, std::vector<double>& delta_t)
{
	std::vector<double> arr(6, 0);
	for (int i = 0; i < 6; i++)
	{
		double t_i = avarage[i] / 1000;
		double tt = std::pow(t_i, 4);
		double te = tt;
		double c_h = 4 / (9 * std::pow(t_i, 4));
		double c_v_0 = 4 / (9 * std::pow(t_i, 2));
		double c_t = ((2 * V_0 * t_i - 4 * H) / (t_i * t_i * t_i)) * ((2 * V_0 * t_i - 4 * H) / (t_i * t_i * t_i));
		arr[i] = sqrt(c_h * omega_h * omega_h + c_v_0 * omega_v_0 * omega_v_0 + (delta_t[i] * delta_t[i] * c_t / 1000000));
	}

	return arr;

}


int main()
{

	std::vector<std::vector<double>> t =
	{
		{1,153.963,153.692,152.337,154.324,153.326,153.391},
		{2,153.612,152.895,153.777,154.011,154.178,153.225},
		{3,153.178,153.065,152.616,154.378,153.245,153.900},
		{4,152.978,152.845,152.725,155.019,153.199,153.449},
		{5,153.161,153.401,152.687,154.112,153.737,152.773},
		{6,152.647,152.962,154.121,154.393,154.022,153.258},
		{7,153.265,152.633,152.557,154.121,153.335,152.291},
		{8,153.572,152.806,153.033,154.101,154.341,154.345},
		{9,153.623,152.819,153.153,154.989,154.471,152.916},
		{10,152.611,152.751,152.401,154.949,153.404,152.599},
		{11,153.421,152.841,152.678,154.606,153.550,153.426},
		{12,154.882,152.773,152.277,154.464,153.451,153.675},
		{13,152.989,152.850,152.409,155.113,153.386,153.938},
		{14,152.824,152.751,152.603,154.778,153.501,153.684},
		{15,152.783,152.702,152.853,153.991,153.400,153.276},
		{16,152.746,152.724,152.832,154.140,153.963,152.910},
		{17,152.842,152.884,153.355,154.445,153.233,154.140},
		{18,152.891,152.496,153.667,154.196,154.007,153.345},
		{20,154.131,152.747,152.785,154.473,153.864,153.651},
		{21,152.993,152.873,152.737,154.428,153.449,152.719},
		{22,153.223,153.818,152.678,153.973,154.632,153.106},
		{23,152.919,152.840,152.504,154.395,153.454,152.807},
		{24,153.328,152.903,153.240,154.187,153.939,153.140},
		{25,152.746,152.838,152.891,154.339,153.230,153.009},
		{26,152.994,153.153,153.839,154.208,153.881,153.000},
		{27,153.937,153.566,152.704,153.774,153.907,153.333},
		{28,153.441,153.451,152.919,154.772,153.796,153.048},
		{29,153.144,152.873,153.478,154.012,153.453,153.144},
		{30,153.325,152.093,152.752,154.277,153.361,153.804}
	};
	std::vector<double> avarage(6, 0);

	for (int i = 1; i < 7; ++i)
	{
		double sum = 0.0;
		for (int j = 0; j < 29; ++j)
		{
			sum += t[j][i];
		}
		avarage[i - 1] = sum / t.size();
	}

	std::ofstream outputFile("avarageTime.csv");
	for (int i = 0; i < 6; i++)
	{
		outputFile << avarage[i] << "\n";
	}
	outputFile.close();

	std::vector<double> stDevArr = delta_T(t, avarage);

	std::ofstream out("delta_t.csv");
	for (int i = 0; i < 6; i++)
	{
		out << stDevArr[i] << "\n";
	}
	out.close();

	std::vector<double> g_ = g(avarage);
	std::ofstream outt("g.csv");
	for (int i = 0; i < 6; i++)
	{
		outt << g_[i] << "\n";
	}
	outt.close();

	std::vector<double> d_g = delta_g(avarage, stDevArr);
	std::ofstream outtt("delta_g.csv");
	for (int i = 0; i < 6; i++)
	{
		outtt << d_g[i] << "\n";
	}
	outtt.close();

	return 0;
}