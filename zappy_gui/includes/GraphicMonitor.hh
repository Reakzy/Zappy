/*
** GraphicMonitor.hh for zappy_gui in /home/werp/rendu/zappy_gui/GraphicMonitor.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Tue Jun 20 11:34:47 2017 Paul Wéry
// Last update Sun Jul  2 00:15:35 2017 Wéry
*/

#ifndef ZAPPY_GUI_GRAPHICMONITOR_HH
# define ZAPPY_GUI_GRAPHICMONITOR_HH

# include <queue>
# include <memory>
# include "InterpretProtocol.hh"
# include "EventReceiver.hh"
# include "ParserJson.hh"
# include "Socket.hh"
# include "Players.hh"
# include "Gate.hh"
# include "SoundLoader.hh"
# include "TextPanel.hh"

class GraphicMonitor
{
 public:

  enum class TypeNodes
  {
    MAP = 0,
    PLAYERS,
    EGGS,
    OBJECTS,
    GATES
  };

  typedef std::shared_ptr<std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>> NodeList;

 private:

  Socket						socket;
  ActionsManager					actionsManager;
  ExecuteActions					executeActions;
  InterpretProtocol					interpretProtocol;
  EventReceiver						eventReceiver;
  ParserJson						parserJson;
  irr::IrrlichtDevice					*device;
  irr::scene::ICameraSceneNode				*camera;
  std::map<irr::EKEY_CODE, irr::core::vector3df>	cameraPositions;
  std::vector<irr::scene::ILightSceneNode*>		light;
  std::queue<std::string>				msgQueue;
  bool							connected;
  irr::gui::IGUIImage					*stonesPanel;
  TextPanel						teamsPanel;
  TextPanel						broadcastPanel;
  irr::gui::IGUIImage					*background;
  irr::gui::IGUIImage					*credits;

  NodeList						map;
  NodeList						playersNodes;
  NodeList						eggs;
  NodeList						objects;
  NodeList						gatesNodes;

  std::vector<std::shared_ptr<Players>>			players;
  std::vector<std::shared_ptr<Gate>>			gates;
  std::map<TypeNodes, NodeList> 			allNodes;

  unsigned int						frequency;
  std::map<std::string, std::vector<irr::s32>>		animations;

  std::map<std::string, std::shared_ptr<SoundLoader>>	sounds;

 public:

  NodeList				&getNodes(TypeNodes type);
  void					newPlayer(const std::string &num);
  void					deadPlayer(const std::string &num);
  std::shared_ptr<Players>		getPlayer(const std::string &num) const;
  void					newGate(const std::string &numBlueGate, const std::string &numOrangeGate);
  std::shared_ptr<Gate>			getGate(const std::string &numBlueGate) const;
  void					setGateFrequency(unsigned int frequency);

  void					clearNodes();
  irr::scene::ISceneManager		*getSceneManager() const;
  irr::video::IVideoDriver		*getVideoDriver() const;
  void					setPosTargetCamera(const irr::core::vector3df &position);
  void					setPosLight(const irr::core::vector3df &position, irr::f32 width);
  void					setRadiusLight(irr::f32 radius);

  bool					connectGraphic(const std::string &ip, const std::string &port);
  bool					connectionEstablished();
  bool					startDevice();
  void					launchGraphic();
  void					loadAnimationsPlayer();
  void					loadSounds();
  void					drawInfoPanels();
  void					setFrequency(unsigned int frequency);
  void					doAnimations() ;
  void					playSound(const std::string &sound);
  void					playMusic(const std::string &music);
  void					stopMusic(const std::string &music);

  TextPanel				&getTeamsPanel();
  TextPanel				&getBroadcastPanel();
  void					reversePanelsVisibility();

  void					addCameraPosition(irr::EKEY_CODE key, const irr::core::vector3df &position);
  irr::scene::ICameraSceneNode		*getCamera() const;
  void					changeCameraPosition(irr::EKEY_CODE key);
  void					changeCameraMode(const irr::core::vector3df position,
							 const irr::core::vector3df rotation,
							 const irr::core::vector3df target, bool inputReceiver);

  const std::map<std::string, std::vector<irr::s32>>	&getAnimations() const;
  irr::gui::IGUIImage					*getCredits();

  GraphicMonitor();
  GraphicMonitor(const GraphicMonitor &) = delete;
  ~GraphicMonitor();
  GraphicMonitor			&operator=(const GraphicMonitor &) = delete;
};


#endif //ZAPPY_GUI_GRAPHICMONITOR_HH
