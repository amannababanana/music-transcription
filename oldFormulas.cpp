#if 0
#error everything in here is old stuff
/*****************************
double resonate(std::vector<std::vector<short>> waveform, ALsizei sampleRate, float noteFreq, ALsizei startPos)
{
	// k is spring constant
	double k = (2 * M_PI * noteFreq / sampleRate);
	k *= k;
	//make sure it doesn't go out of bounds
	if (startPos > waveform[0].size() - 3 * sampleRate / noteFreq)
	{
		startPos = waveform[0].size() - 3 * sampleRate / noteFreq;
	}
	//fancy resonation stuff
	std::vector<double> data;
	double x = 0, x_deriv = 0, x_deriv2 = 0;
	std::ofstream log;
	log.open("log.csv", std::ios_base::trunc);
	for (int i = 0; i < 3 * sampleRate / noteFreq; i++)
	{
		x_deriv2 = (waveform[0][i + startPos]) - x*k;
		x_deriv += x_deriv2;
		x += x_deriv;
		data.push_back(x);
		log << x << ',';
		log << waveform[0][i + startPos] << '\n';
	}
	//find 2nd peak
	char countdown = 2;
	double max = 0;
	bool active = false;
	int pos = 0;
	for (int i = 3; i < data.size(); i++)
	{
		if (data[i]>max)
		{
			active = true;
			max = data[i];
		}
		else if (active)
		{
			pos = i - 1;
			active = false;
			countdown--;
			std::cout << max << '\n';
		}
		if (countdown == 0)
		{
			log << max << ',' << pos << '\n';
			log.close();
			return max / pos;
		}
	}
	log.close();
	return -1;
}

std::vector<std::vector<double>> sinWaveDetect(std::vector<std::vector<short>> waveform, ALsizei sampleRate)
{
	std::vector<std::vector<double>> retval;
	std::ofstream log;
	log.open("log2.csv", std::ios_base::trunc);
	for (int i = 0; i < 480; i++)//this is most likely overkill
	{
		retval.push_back(std::vector<double>());
		//for (int j = 0; j < waveform[0].size(); j+=sampleRate/10)
		int j = 2000;
		{
			double d = resonate(waveform, sampleRate, getFreqfromID(i), j);
			retval[i].push_back(d);
			std::cout << d;
			log << d << ',';
		}
		log << std::endl;
	}
	return retval;
}
**************************/
#endif