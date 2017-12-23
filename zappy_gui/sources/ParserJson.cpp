/*
** ParserJson.cpp for cpp_indie_studio in /home/werp/rendu/cpp_indie_studio/ParserJson.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Wed May 24 15:56:33 2017 Paul Wéry
** Last update Wed May 24 15:56:33 2017 Paul Wéry
*/

#include "ParserJson.hh"

ParserJson::ParserJson()
{
  try
    {
      this->regexContent.assign("\"[^{}\"]*[^:]*[^{}]*\\{[^{}]*\\}");
      this->regexLabel.assign("^\"[^\"]*");
      this->regexBloc.assign("\\{[^{}]*\\}");
      this->regexLine.assign("[^{},\\s]([^{},\\[]*?(?=\\[)[^{}\\]]*]|[^{},]*[^{},])");
      this->regexKeyValue.assign("[^\\s:]([^:]*[^\\s:]){0,}");
      this->regexTab.assign("([^\\[\\],\\s][^\\[\\],]*[^\\[\\],\\s])|([^\\[\\],\\s])");
    }
  catch (std::regex_error &e)
    {
      std::cerr << "Constructor : " << e.what() << std::endl;
    }
  success = false;
  pathFile = "";
}

ParserJson::~ParserJson()
{

}

bool ParserJson::getBufferFile(std::string &buffer, const std::string &pathFile) const
{
  std::ifstream	file(pathFile.c_str(), std::ios::in);
  std::string		line;

  if (file)
    {
      while (getline(file, line))
	buffer += line + "\n";
      file.close();
      return (true);
    }
  else
    {
      std::cerr << pathFile << " can't be opened !" << std::endl;
      return (false);
    }
}

bool ParserJson::loadFile(const std::string &pathFile)
{
  std::string				buffer;
  std::string				contentString;

  if (this->pathFile == pathFile)
    return (true);
  if ((success = getBufferFile(buffer, pathFile)))
    {
      this->pathFile = pathFile;
      try
	{
	  blocsString.reset(new std::map<std::string, ParserJson::Data>);
	  std::sregex_iterator next(buffer.begin(), buffer.end(), this->regexContent);
	  std::sregex_iterator end;
	  std::smatch match;
	  while (next != end)
	    {
	      match = *next;
	      contentString = match.str();
	      std::sregex_iterator label(contentString.begin(), contentString.end(), this->regexLabel);
	      std::sregex_iterator bloc(contentString.begin(), contentString.end(), this->regexBloc);
	      match = *bloc;
	      this->bloc.reset(new valuesKeyString);
	      parseAttributs(match.str());
	      match = *label;
	      this->blocsString->insert(std::make_pair(rmQuote(match.str()), this->bloc));
	      next++;
	    }
	}
      catch (std::regex_error &e)
	{
	  std::cerr << "loadFile : " << e.what() << std::endl;
	}
    }
  return (success);
}

void ParserJson::parseAttributs(const std::string &attributs)
{
  try
    {
      std::sregex_iterator next(attributs.begin(), attributs.end(), this->regexLine);
      std::sregex_iterator end;
      while (next != end)
	{
	  std::smatch match = *next;
	  parseLine(match.str());
	  next++;
	}
    }
  catch (std::regex_error &e)
    {
      std::cerr << "parseAttributs : " << e.what() << std::endl;
    }
}

void ParserJson::parseLine(const std::string &line)
{
  unsigned int	idElem = 0;
  std::string		key;
  std::string		value;

  try
    {
      std::sregex_iterator next(line.begin(), line.end(), this->regexKeyValue);
      std::sregex_iterator end;
      while (next != end)
	{
	  std::smatch match = *next;
	  if (idElem % 2 != 0)
	    {
	      value = match.str();
	      fullStruct(key, value);
	    }
	  else
	    key = match.str();
	  idElem++;
	  next++;
	}
    }
  catch (std::regex_error &e)
    {
      std::cerr << "parseLine : " << e.what() << std::endl;
    }
}

void ParserJson::fullStruct(const std::string &key, const std::string &value)
{
  if (key.size() > 0 && value.size() > 0)
    {
      if (value.at(0) == '[')
	parseTab(key, value);
      else if (value.at(0) == '\"')
	this->bloc->stringValues.insert(std::make_pair(rmQuote(key), rmQuote(value)));
      else
	this->bloc->numericValues.insert(std::make_pair(rmQuote(key), std::atof(value.c_str())));
    }
}

void ParserJson::parseTab(const std::string &key, const std::string &tab)
{
  std::vector<std::string>	stringValues;
  std::vector<double>		numericValues;
  bool			string = false;
  bool 			numeric = false;

  try
    {
      std::sregex_iterator next(tab.begin(), tab.end(), this->regexTab);
      std::sregex_iterator end;
      while (next != end)
	{
	  std::smatch match = *next;
	  if (match.str().at(0) == '\"')
	    {
	      string = true;
	      stringValues.push_back(rmQuote(match.str()));
	    }
	  else
	    {
	      numeric = true;
	      numericValues.push_back(std::atof(match.str().c_str()));
	    }
	  next++;
	}
      if (string)
	this->bloc->stringTabValues.insert(std::make_pair(rmQuote(key), stringValues));
      if (numeric)
	this->bloc->numericTabValues.insert(std::make_pair(rmQuote(key), numericValues));
    }
  catch (std::regex_error &e)
    {
      std::cerr << "parseLine : " << e.what() << std::endl;
    }
}

std::string ParserJson::rmQuote(const std::string &str) const
{
  std::string		noQuote;

  for (unsigned int index = 0; index < str.size(); index++)
    {
      if (str.at(index) != '\"')
	{
	  noQuote += str.at(index);
	}
    }
  return (noQuote);
}

std::shared_ptr<std::map<std::string, ParserJson::Data>> ParserJson::getBlocsString() const
{
  if (!success)
    return (nullptr);
  return (this->blocsString);
}

ParserJson::Data ParserJson::getBlocString(const std::string &key) const
{
  std::map<std::string, Data>::iterator	it;

  if (!success)
    return (nullptr);
  if ((it = this->blocsString->find(key)) != this->blocsString->end())
    return (it->second);
  return (nullptr);
}