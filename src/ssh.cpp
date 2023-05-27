#include "ssh.h"

using namespace libssh;

SSHSession::SSHSession(const std::string &host, const std::string &user, const std::string &password, int port)
    : m_session(nullptr), m_host(host), m_user(user), m_password(password), m_port(port)
{
    m_session = ssh_new();
    if (m_session == nullptr)
    {
        std::cerr << "ssh_new failed\n";
        throw std::runtime_error("failed to ssh_new!");
    }
}

SSHSession::~SSHSession()
{
    disconnect();
    ssh_free(m_session);
}

void SSHSession::setHost(const std::string &host)
{
    m_host = host;
}

void SSHSession::setUser(const std::string &user)
{
    m_user = user;
}

void SSHSession::setPassword(const std::string &passwd)
{
    m_password = passwd;
}

bool SSHSession::connect()
{
    ssh_options_set(m_session, SSH_OPTIONS_HOST, m_host.c_str());
    ssh_options_set(m_session, SSH_OPTIONS_USER, m_user.c_str());
    ssh_options_set(m_session, SSH_OPTIONS_PORT, &m_port);
    int status = ssh_connect(m_session);
    if (status != SSH_OK)
    {
        std::cerr << "Failed to connect session\n";
        m_is_connected = false;
        return false;
    }
    m_is_connected = true;
    return true;
}

bool SSHSession::login()
{
    if (!m_is_connected)
    {
        m_is_logined = false;
        return false;
    }
    int status = ssh_userauth_password(m_session, nullptr, m_password.c_str());
    if (status != SSH_AUTH_SUCCESS)
    {
        std::cerr << "Failed to login\n";
        m_is_logined = false;
        return false;
    }
    m_is_logined = true;
    return true;
}

bool SSHSession::isConnected() const
{
    return m_is_connected;
}

bool SSHSession::isLogined() const
{
    return m_is_logined;
}

std::unique_ptr<SSHChannel> SSHSession::createChannel()
{
    if (!isConnected())
    {
        return nullptr;
    }
    return std::make_unique<SSHChannel>(*this);
}

ssh_session &SSHSession::getSession()
{
    return m_session;
}

bool SSHSession::disconnect()
{
    if (m_is_connected)
    {
        ssh_disconnect(m_session);
        return true;
    }
    return false;
}

SSHChannel::SSHChannel(SSHSession &session)
    : session(session), channel(nullptr)
{
    if (!session.isConnected())
    {
        throw std::runtime_error("Failed to create SSH channel: session not connected");
    }
    channel = ssh_channel_new(session.getSession());
    if (!channel)
    {
        std::cerr << "ssh_channel_new failed\n";
        std::cerr << std::string(ssh_get_error(session.getSession()));
        throw std::runtime_error("Failed to create SSH channel");
    }
}

SSHChannel::~SSHChannel()
{
    if (channel)
    {
        close();
        ssh_channel_free(channel);
    }
}

bool SSHChannel::isOpened() const
{
    return is_opened;
}

bool SSHChannel::open()
{
    if (isOpened())
    {
        return true;
    }

    if (!session.isConnected() || !session.isLogined())
    {
        is_opened = false;
        return false;
    }

    int status = ssh_channel_open_session(channel);
    if (status != SSH_OK)
    {
        std::cerr << "failed to open channel\n";
        is_opened = false;
        return false;
    }
    is_opened = true;
    return true;
}

bool SSHChannel::execute(const std::string &command)
{
    if (!isOpened())
    {
        open();
    }

    int status = ssh_channel_request_exec(channel, command.c_str());
    if (status != SSH_OK)
    {
        return false;
    }

    return true;
}

std::string SSHChannel::read()
{
    if (!isOpened())
    {
        return "";
    }
    std::string output;
    const int READ_BUFFER_SIZE = 4096;
    char buffer[READ_BUFFER_SIZE] = {0};
    int nbytes = 0;
    while (nbytes = ssh_channel_read(channel, buffer, READ_BUFFER_SIZE, 0))
    {
        if (nbytes < 0)
        {
            std::cerr << "Error reading from channel\n";
            return output;
        }
        std::cout << "read " << nbytes << "\n";
        output.append(buffer, nbytes);
    }
    return output;
}

bool SSHChannel::close()
{
    if (!isOpened())
    {
        return false;
    }
    ssh_channel_close(channel);
    is_opened = false;
    return true;
}

SSHClient::SSHClient(const std::string &host, const std::string &username, const std::string &password, int port)
    : session(host, username, password, port) {}

SSHClient::~SSHClient()
{
    disconnect();
}

bool SSHClient::connect()
{
    if (!session.connect() || !session.login())
    {
        return false;
    }
    return true;
}

bool SSHClient::disconnect()
{
    if (!session.disconnect())
    {
        return false;
    }
    connected = false;
    return true;
}

bool SSHClient::execute(const std::string &command, std::string &output)
{
    auto channel = session.createChannel();
    if (!channel)
    {
        return false;
    }
    if (!channel->execute(command))
    {
        return false;
    }

    output = channel->read();
    return true;
}

bool SSHClient::isConnected()
{
    return connected;
}