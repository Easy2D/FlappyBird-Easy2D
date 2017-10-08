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
	if ((fp = _wfopen(_T("res/atlas.bin"), _T("r"))) == NULL) {
		return false;
	}

	// 从文件读取数据
	while (fgetws(str, 50, fp) != NULL) {
		TCHAR name[21];
		int width, height, x, y;
		// 读取图片名称、宽高、起始点坐标
		swscanf(str, _T("%s %d %d %d %d"), name, &width, &height, &x, &y);
		// 创建 IMAGE_INFO
		IMAGE_INFO info = { x, y, width, height };
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
