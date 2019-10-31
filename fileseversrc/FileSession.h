#pragma once
#include "../net/Buffer.h"
#include "TcpSession.h"

class FileSession :public TcpSession
{
public:
    FileSession(const std::shared_ptr<TcpConnection>& coon,const char* filebasedir);
    virtual ~FileSession();
    
    FileSession(const FileSession& rhs) = delete;
    FileSession& operator=(const FileSession& rhs) = delete;

    void OnRead(const std::shared_ptr<TcpConnection>& coon, Buffer* pBuffer, Timestamp receivTime); 


private:
    //64位机器上，size_t是8个字节
    bool Process(const std::shared_ptr<TcpConnection>& conn, const char* inbuf, size_t length);
    
    bool OnUploadFileResponse(const std::string& filemd5, int64_t offset, int64_t filesize, const std::string& filedata, const std::shared_ptr<TcpConnection>& conn);
    bool OnDownloadFileResponse(const std::string& filemd5, int32_t clientNetType, const std::shared_ptr<TcpConnection>& conn);

    void ResetFile();


private:    
    int32_t m_id;
    int32_t m_seq;

    FILE* m_fp{};
    int64_t m_currentDownloadFileOffset{};
    int64_t m_currentDownloadFileSize{};
    std::string m_strFileBaseDir;
    bool        m_bFileUploading;

};