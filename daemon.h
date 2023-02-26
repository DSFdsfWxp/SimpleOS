#ifndef simpleOS_daemon_h
#define simpleOS_daemon_h

class daemon_t
{
public:
    virtual void start();
    virtual ~daemon_t();
};

class daemonGroup_t
{
public:
    daemon_t *keyScanD;

    template <typename daemonT>
    void startDaemon(daemon_t *&ptr)
    {
        if (ptr != 0)
        {
            return;
        }
        ptr = (daemon_t *)(new daemonT());
        ptr->start();
    }

    void stopDaemon(daemon_t *&ptr);
};

#endif