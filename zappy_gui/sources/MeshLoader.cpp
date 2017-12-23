/*
** MeshLoader.cpp for zappy_gui in /home/werp/rendu/zappy_gui/MeshLoader.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Wed Jun 21 14:45:13 2017 Paul Wéry
** Last update Wed Jun 21 14:45:13 2017 Paul Wéry
*/

#include "MeshLoader.hh"

MeshLoader::MeshLoader(irr::scene::ISceneManager *_scene, irr::video::IVideoDriver *_driver)
: scene(_scene), driver(_driver)
{
  frequency = 1;
}

MeshLoader::~MeshLoader()
{

}

irr::scene::IAnimatedMeshSceneNode *MeshLoader::loadAsset(const std::string &asset, const std::string &fileName)
{
  irr::scene::IAnimatedMeshSceneNode	*node;
  ParserJson::Data			bloc;

  if (!parserJson.loadFile(fileName) || (bloc = parserJson.getBlocString(asset)).get() == nullptr)
    return (nullptr);
  node = loadMesh(bloc);
  if (isValidNode(node, bloc))
    return (node);
  return (nullptr);
}

irr::scene::IAnimatedMeshSceneNode *MeshLoader::loadMesh(ParserJson::Data bloc) const
{
  irr::scene::IAnimatedMesh *mesh;

  if (bloc->stringValues.find("mesh") == bloc->stringValues.end()
      || (mesh = scene->getMesh(bloc->stringValues.find("mesh")->second.c_str())) == nullptr)
    return (nullptr);
  return (scene->addAnimatedMeshSceneNode(mesh));
}

bool MeshLoader::isValidNode(irr::scene::IAnimatedMeshSceneNode *node,
			     ParserJson::Data bloc) const
{
  if (node == nullptr)
    return (false);
  node->setAnimationSpeed(24);
  loadTexture(node, bloc);
  loadPosRot(node, bloc);
  loadScale(node, bloc);
  node->setLoopMode(false);
  node->setFrameLoop(0, 0);
  node->setCurrentFrame(0);
  return (true);
}

bool MeshLoader::loadTexture(irr::scene::IAnimatedMeshSceneNode *node,
			     ParserJson::Data bloc) const
{
  irr::video::ITexture		*texture;

  if (bloc->stringValues.find("texture") == bloc->stringValues.end())
    {
      for (unsigned int index = 0; index < node->getMaterialCount(); index++)
	{
	  node->getMaterial(index).NormalizeNormals = true;
	  node->getMaterial(index).Lighting = true;
	}
    }
  else
    {
      if ((texture = driver->getTexture(bloc->stringValues.find("texture")->second.c_str())) == nullptr)
	return (false);
      node->setMaterialTexture(0, texture);
    }
  return (true);
}

bool MeshLoader::loadPosRot(irr::scene::IAnimatedMeshSceneNode *node,
			    ParserJson::Data bloc) const
{
  std::map<std::string, std::vector<double>>::iterator	info;

  info = bloc->numericTabValues.find("position");
  if (info == bloc->numericTabValues.end() || info->second.size() != 3)
    return (false);
  node->setPosition(irr::core::vector3df(static_cast<irr::f32>(info->second.at(0)),
					 static_cast<irr::f32>(info->second.at(1)),
					 static_cast<irr::f32>(info->second.at(3))));
  info = bloc->numericTabValues.find("rotation");
  if (info == bloc->numericTabValues.end() || info->second.size() != 3)
    return (false);
  node->setRotation(irr::core::vector3df(static_cast<irr::f32>(info->second.at(0)),
					 static_cast<irr::f32>(info->second.at(1)),
					 static_cast<irr::f32>(info->second.at(3))));
  return (true);
}

bool MeshLoader::loadScale(irr::scene::IAnimatedMeshSceneNode *node,
			   ParserJson::Data bloc) const
{
  std::map<std::string, std::vector<double>>::iterator	info;

  info = bloc->numericTabValues.find("scale");
  if (info == bloc->numericTabValues.end() || info->second.size() != 3)
    return (false);
  node->setScale(irr::core::vector3df(static_cast<irr::f32>(info->second.at(0)),
				      static_cast<irr::f32>(info->second.at(1)),
				      static_cast<irr::f32>(info->second.at(2))));
  return (true);
}

void MeshLoader::setFrequency(unsigned int frequency)
{
  this->frequency = frequency;
}
