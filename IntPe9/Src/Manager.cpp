#include "Manager.h"

Manager::Manager(QString path)
{
	readCores(path);
	_activeSniffer = NULL;
	_snifferList = new SnifferList(&_sniffers, &_activeSniffer);
	_coreList = new CoreList(&_cores);
}

Manager::~Manager()
{
	delete _snifferList;
	delete _coreList;
}

void Manager::updateSniffers()
{

}

void Manager::stop()
{
	Sniffer *sniffer;
	foreach(sniffer, _sniffers)
		sniffer->stop();
}

void Manager::activeSaveAll()
{
	if(_activeSniffer != NULL)
		_activeSniffer->savePacketsToFile();
}

void Manager::registerSniffer(Sniffer *sniffer)
{
	_activeSniffer = sniffer;
	_sniffers.push_back(sniffer);

	//Connect the models
	connect(sniffer->getPacketList(), SIGNAL(layoutChanged()), _snifferList, SLOT(refresh()));
	_snifferList->refresh();

	emit activeSnifferChanged(sniffer);
}

void Manager::readCores(QString path)
{
	QDir dir(path);
	QStringList filter("*.dll");
	dir.setNameFilters(filter);
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	QFileInfoList list = dir.entryInfoList();

	QSettings settings(INI_FILE, QSettings::IniFormat);
	for (int i = 0; i < list.size(); ++i)
	{
		const QFileInfo *fileInfo = &list.at(i);
		Core *core = new Core(fileInfo);
		core->setEnabled(settings.value(INI_S_AUTO_INJECT+core->getName(), false).toBool());
		_cores.push_back(core);
	}
}

/************************************************************************/
/*                           Property's                                 */
/************************************************************************/
QVector<Sniffer*> *Manager::getSniffers()
{
	return &_sniffers;
}

QVector<Core*> *Manager::getCores()
{
	return &_cores;
}

Sniffer *Manager::getActiveSniffer()
{
	return _activeSniffer;
}

void Manager::setActiveSniffer(const QModelIndex &index)
{
	_activeSniffer = _sniffers.at(index.row());
	_snifferList->refresh();
	emit activeSnifferChanged(_activeSniffer);
}
bool Manager::hasSniffer(int32 pid)
{
	Sniffer *sniffer;
	foreach(sniffer, _sniffers)
		if(sniffer->getPid() == pid)
		return true;
	return false;
}

Core *Manager::getCore(QString name, bool enabled)
{
	Core *core;
	foreach(core, _cores)
		if(core->getProcessName() == name && core->isEnabled() == enabled)
			return core;
	return NULL;
}

SnifferList *Manager::getSnifferModel()
{
	return _snifferList;
}

CoreList *Manager::getCoreModel()
{
	return _coreList;
}