#include "ImageLoader.h"

typedef struct
{
	int x, y, width, height;
} IMAGE_INFO;

static std::map<TString, IMAGE_INFO> m_Images;


bool ImageLoader::init()
{
	FILE *fp;
	TCHAR str[51];
	if ((fp = _wfopen(_T("res/atlas.bin"), _T("rt"))) == NULL) {
		return false;
	}

	// ���ļ���ȡ����
	while (fgetws(str, 50, fp) != NULL) {
		TCHAR name[21];
		float x, y;
		int width, height;
		// ��ȡͼƬ���ơ���ߡ���ʼ������
		swscanf(str, _T("%s %d %d %f %f"), name, &width, &height, &x, &y);
		x *= 1024;
		y *= 1024;
		// ���� IMAGE_INFO
		IMAGE_INFO info = { int(x), int(y), width, height };
		m_Images.insert(make_pair(TString(name), info));
	}

	fclose(fp);
	return true;
}

Image * ImageLoader::getImage(TString imageName)
{
	IMAGE_INFO info = m_Images.at(imageName);
	return new Image(_T("res/atlas.png"), info.x, info.y, info.width, info.height);
}
