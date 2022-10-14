#include "ResLoader.h"
#include "resource.h"
#include <sstream>

Image* image = nullptr;
std::map<String, ResLoader::ImageInfo> ResLoader::imageMap;
std::map<MusicType, Music*> ResLoader::musicMap;

void ResLoader::init()
{
	// Ԥ����ͼƬ
	image = Image::load(IDB_PNG1, L"PNG");

	// �� atlas.txt �ļ�
	Resource atlas(IDR_TXT1, L"TXT");
	Resource::Data data = atlas.loadData();
	// ��ȡ�ļ�����
	std::stringstream sstream;
	sstream << data;
	// ��ȡͼƬ��Ϣ
	while (!sstream.eof())
	{
		char name[21];
		float width, height, x, y;
		// ��ȡͼƬ���ơ���ߡ���ʼ������
		sstream >> name >> width >> height >> x >> y;
		// ���� Info
		ImageInfo info = { x, y, width, height };
		// �����ƴ�խ�ַ���תΪ���ַ���
		String wideName = NarrowToWide(name);
		// ���浽��ͼ��
		imageMap.insert(std::make_pair(wideName, info));
	}

	// ������Ƶ
	int wavId[] = { WAV_CLICK, WAV_FLY, WAV_HIT, WAV_POINT, WAV_SWOOSH };
	MusicType wavName[] = { MusicType::Click, MusicType::Fly, MusicType::Hit, MusicType::Point, MusicType::Swoosh };
	for (int i = 0; i < ARRAYSIZE(wavId); i++)
	{
		// ʹ�ò�����Ԥ������Ƶ
		Music* music = MusicPlayer::preload(wavId[i], L"WAVE");
		// ���浽��ͼ��
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
