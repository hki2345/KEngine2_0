#pragma once
#include <iostream>
#include <vector>



class KFileStream
{
private:
	// 본체에서는 해야하니까
	KFileStream() {} /* = delete*/;
	KFileStream(const KFileStream& _Stream) = delete;
	KFileStream(const KFileStream&& _Stream) = delete;
	void operator=(const KFileStream& _Stream) = delete;
	~KFileStream() {};


	static KFileStream* pKFileStream;


public:
	static KFileStream* instance()
	{
		if (nullptr == pKFileStream)
		{
			pKFileStream = new KFileStream();
		}
		return pKFileStream;
	}

	void release();


public:
	template<typename T>
	bool write_file(const wchar_t* _Path, const T& _File)
	{
		FILE* TFILE;
		_wfopen_s(&TFILE, _Path, L"w");
		fwrite(&_File, sizeof(_File), 1, TFILE);
		fclose(TFILE);

		return true;
	}

	template<typename T>
	bool read_file(const wchar_t* _Path, T& _File)
	{
		FILE* TFILE;
		_wfopen_s(&TFILE, _Path, L"r");
		fread_s(&_File, sizeof(_File), sizeof(_File), 1, TFILE);
		fclose(TFILE);

		return true;
	}
};

