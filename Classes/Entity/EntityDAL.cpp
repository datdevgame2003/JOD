//#include "EntityDAL.h"
//#include "json/rapidjson.h"
//#include "json/document.h"
//
//EntityDAL::EntityDAL(std::string entityName)
//{
//    rapidjson::Document docs;
//
//    std::string dataContent = cocos2d::FileUtils::getInstance()->getStringFromFile("Data/Entity/" + entityName + ".json");
//    docs.Parse(dataContent.c_str());
//
//    auto dataArray = docs["data"].GetArray();
//
//    for (int i = 0; i < dataArray.Size(); ++i)
//    {
//        int hp = dataArray[i]["_hp"].GetInt();
//        int atk = dataArray[i]["_atk"].GetInt();
//        int spd = dataArray[i]["_spd"].GetFloat();
//        int aspd = dataArray[i]["_aspd"].GetFloat();
//
//        EntityStat* stat = new EntityStat();
//        stat->_health = hp;
//        stat->_attack = atk;
//        stat->_runSpeed = spd;
//        stat->_attackSpeed = aspd;
//
//        _stats.push_back(stat);
//    }
//}
//
//EntityStat* EntityDAL::getEntityStat(int level)
//{
//    if (level < 1 || level > _stats.size())
//    {
//        return nullptr;
//    }
//    return _stats[level - 1];
//}