/*
** VolumeLight.cpp for zappy_gui in /home/werp/rendu/zappy_gui/VolumeLight.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Wed Jun 28 15:34:18 2017 Paul Wéry
** Last update Wed Jun 28 15:34:18 2017 Paul Wéry
*/

# include "VolumeLight.hh"

VolumeLight::VolumeLight(irr::scene::ISceneManager *_sceneManager, irr::video::IVideoDriver *_videoDriver)
: sceneManager(_sceneManager), videoDriver(_videoDriver)
{
  this->speed = 50;
  this->volumeLight = sceneManager->addVolumeLightSceneNode();
}

VolumeLight::~VolumeLight()
{
  if (volumeLight != nullptr)
    volumeLight->remove();
}

void VolumeLight::loadVolumeLight(const std::string &fileConf, const std::string &animation)
{
  ParserJson::Data	bloc;

  if (volumeLight == nullptr || !parserJson.loadFile(fileConf) || !loadTextures(animation))
    return ;
  if ((bloc = parserJson.getBlocString(animation)).get() != nullptr
      && bloc->numericValues.find("Speed") != bloc->numericValues.end())
    {
      this->speed = static_cast<unsigned int>(bloc->numericValues.find("Speed")->second);
    }
  textureAnimator = sceneManager->createTextureAnimator
   (textures, static_cast<irr::s32>(this->speed));
  volumeLight->addAnimator(textureAnimator);
  textureAnimator->drop();

}

bool VolumeLight::loadTextures(const std::string &animation)
{
  ParserJson::Data		bloc;
  std::string			path;
  std::vector<std::string>	images;
  std::string			pathImage;
  irr::video::ITexture		*texture;

  if ((bloc = parserJson.getBlocString(animation)).get() == nullptr
      || bloc->stringValues.find("Path") == bloc->stringValues.end()
      || bloc->stringTabValues.find("Images") == bloc->stringTabValues.end())
    return (false);
  this->textures.clear();
  path = bloc->stringValues.find("Path")->second;
  images = bloc->stringTabValues.find("Images")->second;
  for (unsigned int index = 0; index < images.size(); index++)
    {
      pathImage = path + images.at(index);
      if ((texture = videoDriver->getTexture(pathImage.c_str())) != nullptr)
	this->textures.push_back(texture);
    }
  return (true);
}

bool &VolumeLight::isUsed()
{
  return (used);
}

std::string &VolumeLight::assignedBloc()
{
  return (keyBloc);
}

irr::scene::IVolumeLightSceneNode *VolumeLight::getVolumeLight()
{
  return (volumeLight);
}
