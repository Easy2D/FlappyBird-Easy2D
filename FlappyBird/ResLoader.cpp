#include "ResLoader.h"
#include "resource.h"
#include <sstream>

Image* image = nullptr;
std::map<String, ResLoader::ImageInfo> ResLoader::imageMap;
std::map<MusicType, Music*> ResLoader::musicMap;

void ResLoader::init()
{
	// 预加载图片
	image = Image::load(IDB_PNG1, L"PNG");

	// 打开 atlas.txt 文件
	Resource atlas(IDR_TXT1, L"TXT");
	Resource::Data data = atlas.loadData();
	// 读取文件内容
	std::stringstream sstream;
	sstream << data;
	// 读取图片信息
	while (!sstream.eof())
	{
		char name[21];
		float width, height, x, y;
		// 读取图片名称、宽高、起始点坐标
		sstream >> name >> width >> height >> x >> y;
		// 创建 Info
		ImageInfo info = { x, y, width, height };
		// 将名称从窄字符串转为宽字符串
		String wideName = NarrowToWide(name);
		// 保存到地图中
		imageMap.insert(std::make_pair(wideName, info));
	}

	// 加载音频
	int wavId[] = { WAV_CLICK, WAV_FLY, WAV_HIT, WAV_POINT, WAV_SWOOSH };
	MusicType wavName[] = { MusicType::Click, MusicType::Fly, MusicType::Hit, MusicType::Point, MusicType::Swoosh };
	for (int i = 0; i < ARRAYSIZE(wavId); i++)
	{
		// 使用播放器预加载音频
		Music* music = MusicPlayer::preload(wavId[i], L"WAVE");
		// 保存到地图中
		musicMap.insert(std::make_pair(wavName[i], music));
	}
}

KeyFrame* ResLoader::getKeyFrame(String imageName)
{
	auto iter = imageMap.find(imageName);
	if (iter == imageMap.end())
	{
		return nullptr;
	}
	ImageInfo info = imageMap.at(imageName);
	return gcnew KeyFrame(image, Rect{ Point{info.x, info.y}, Size{info.width, info.height} });
}

void ResLoader::playMusic(MusicType musicType)
{
	Music* music = musicMap[musicType];
	if (music)
	{
		music->play();
	}
}
