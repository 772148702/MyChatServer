#pragma once

#include<stdint.h>

enum
{
    PACKAGE_UNCOMPRESSED,
    PACKAGE_COMPRESSED
};

enum msg_type
{
    msg_type_unknown,
    msg_type_heartbeat = 1000,     //������
    msg_type_register,             //ע��
    msg_type_login,                //��½
    msg_type_getofriendlist,       //��ȡ�����б�
    msg_type_finduser,             //�����û�
    msg_type_operatefriend,        //���ӡ�ɾ���Ⱥ��Ѳ���
    msg_type_userstatuschange,     //�û���Ϣ�ı�֪ͨ
    msg_type_updateuserinfo,       //�����û���Ϣ
    msg_type_modifypassword,       //�޸ĵ�½����
    msg_type_creategroup,          //����Ⱥ��
    msg_type_getgroupmembers,      //��ȡȺ���Ա�б�
    msg_type_chat   = 1100,        //������Ϣ
    msg_type_multichat,            //Ⱥ����Ϣ
    msg_type_kickuser,             //��������
    msg_type_remotedesktop,        //Զ������
    msg_type_updateteaminfo,       //�����û����ѷ�����Ϣ
    msg_type_modifyfriendmarkname, //���º��ѱ�ע��Ϣ
    msg_type_movefriendtootherteam, //�ƶ�������
};

enum online_type{
    online_type_offline         = 0,    //����
    online_type_pc_online       = 1,    //��������
    online_type_pc_invisible    = 2,    //��������
    online_type_android_cellular= 3,    //android 3G/4G/5G����
    online_type_android_wifi    = 4,    //android wifi����
    online_type_ios             = 5,    //ios ����
    online_type_mac             = 6     //MAC����
};


#pragma pack(push, 1)

struct msg
{
    char     compressflag;     //ѹ����־�����Ϊ1��������ѹ������֮������ѹ��
    int32_t  originsize;       //����ѹ��ǰ��С
    int32_t  compresssize;     //����ѹ�����С
    char     reserved[16];
};

#pragma pack(pop)

enum friend_operation_type
{
    //���ͼӺ�������
    friend_operation_send_add_apply      = 1,
    //���յ��Ӻ�������(���ͻ���ʹ��)
    friend_operation_recv_add_apply,
    //Ӧ��Ӻ�������
    friend_operation_reply_add_apply,
    //ɾ����������
    friend_operation_send_delete_apply,
    //Ӧ��ɾ��������
    friend_operation_recv_delete_apply
};

enum friend_operation_apply_type
{
    //�ܾ��Ӻ���
    friend_operation_apply_refuse,
    //���ܼӺ���
    friend_operation_apply_accept
};


enum updateteaminfo_operation_type
{
    //��������
    updateteaminfo_operation_add,
    //ɾ������
    updateteaminfo_operation_delete,
    //�޸ķ���
    updateteaminfo_operation_modify
};
enum error_code
{
    error_code_ok                   = 0,
    error_code_unknown              = 1,
    error_code_notlogin             = 2,
    error_code_registerfail         = 100,
    error_code_registeralready      = 101,
    error_code_notregister          = 102,
    error_code_invalidpassword      = 103,
    error_code_updateuserinfofail   = 104,
    error_code_modifypasswordfail   = 105,
    error_code_creategroupfail      = 106,
    error_code_toooldversion        = 107,
    error_code_modifymarknamefail   = 108,
    error_code_teamname_exsit       = 109, //�����Ѿ�����
};
