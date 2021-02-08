#pragma once

#ifdef SQLSERVER_EXPORTS
#define SQLSERVER_API __declspec(dllexport)
#else
#define SQLSERVER_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <SQLAPI.h>

class SQLSERVER_API SQLConnection abstract
{
public:
    virtual void Connect(const std::string& database_string, /*serverName@databaseName*/ const std::string& username, const std::string& password) abstract;
    virtual void InsertPhoto(const std::string& photo_path, const std::string& photo_name, const std::string& photo_extension) abstract;
    virtual void RollBack() abstract;
    virtual void Disconnect() abstract;
    virtual void ClearTable() abstract;
};

class SQLSERVER_API SQLServer : public SQLConnection
{
public:
    struct PhotoType
    {
        SAString photoBytes;
        SAString photoName;
        SAString photoExtension;
    };

    SQLServer() = default;
    SQLServer(const std::string& database_string, /*serverName@databaseName*/ const std::string& username, const std::string& password);

    ~SQLServer();

    void Connect(const std::string& database_string, /*serverName@databaseName*/ const std::string& username, const std::string& password);
    void InsertPhoto(const std::string& photo_path, const std::string& photo_name, const std::string& photo_extension);
    std::vector<PhotoType> GetAllPhotos();
    void RollBack();
    void Disconnect();
    void ClearTable();

    static void CreatePhotos(const std::vector<PhotoType>& photos);

protected:
    SAConnection m_connection;
};