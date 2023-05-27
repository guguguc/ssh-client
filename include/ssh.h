#ifndef __SSH__
#define __SSH__

#include <libssh/libssh.h>
#include <string>
#include <iostream>

namespace libssh
{
    class SSHSession
    {
        friend class SSHChannel;

    public:
        SSHSession(const std::string &host, const std::string &user, const std::string &password, int port);
        ~SSHSession();

        void setHost(const std::string &host);
        void setUser(const std::string &user);
        void setPassword(const std::string &passwd);

        bool connect();
        bool login();
        bool isConnected() const;
        bool isLogined() const;
        bool disconnect();

        std::unique_ptr<SSHChannel> createChannel();

    protected:
        ssh_session& getSession();

    private:
        ssh_session m_session{nullptr};
        std::string m_host;
        std::string m_user;
        std::string m_password;
        int m_port{0};
        bool m_is_connected{false};
        bool m_is_logined{false};
    };

    class SSHChannel
    {
    public:
        explicit SSHChannel(SSHSession &session);
        ~SSHChannel();

        bool isOpened() const;
        bool open();
        bool execute(const std::string &command);
        std::string read();
        bool close();

    private:
        SSHSession &m_session;
        ssh_channel m_channel{nullptr};
        bool m_is_opened{false};
    };

    class SSHClient
    {
    public:
        explicit SSHClient(const std::string &host, const std::string &username, const std::string &password, int port = 22);
        ~SSHClient();

        bool connect();
        bool disconnect();
        bool execute(const std::string &command, std::string &output);
        bool isConnected();

    private:
        SSHSession m_session;
        bool m_connected{false};
    };
}

#endif