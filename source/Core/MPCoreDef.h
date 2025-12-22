#pragma once
#include <QObject>

// NOTE: 为了保持命名规则一致，需要设置大小写两种命名

// 此宏用来定义操作一致的属性getset
#define PROPERTY_GETSET(type, propertyName, PropertyName, defaultValue) \
    private: \
    type m##PropertyName{defaultValue}; \
    public: \
    Q_SIGNAL void propertyName##Changed(const type &value); \
    type propertyName() const { \
        return this->m##PropertyName; \
    } \
    void set##PropertyName(const type &value) { \
        if (value != this->m##PropertyName) { \
            this->m##PropertyName = value; \
            Q_EMIT propertyName##Changed(value); \
        } \
    }
// 可读写属性
#define READWRITE_PROPERTY(type, propertyName, PropertyName, defaultValue) \
    private: \
    Q_PROPERTY(type propertyName READ propertyName WRITE set##PropertyName NOTIFY propertyName##Changed) \
    PROPERTY_GETSET(type, propertyName, PropertyName, defaultValue)
// 只读属性
#define READONLY_PROPERTY(type, propertyName, PropertyName, defaultValue) \
    private: \
    Q_PROPERTY(type propertyName READ propertyName NOTIFY propertyName##Changed) \
    PROPERTY_GETSET(type, propertyName, PropertyName, defaultValue)

// 成员属性
#define MEMBER_PROPERTY(type, propertyName, PropertyName, defaultValue) \
    private: \
    Q_PROPERTY(type propertyName MEMBER m##PropertyName NOTIFY propertyName##Changed) \
    type m##PropertyName{defaultValue}; \
    public: \
    Q_SIGNAL void propertyName##Changed(); \
    type propertyName() const { \
        return this->m##PropertyName; \
    } \
    void set##PropertyName(const type &value) { \
        if (value != this->m##PropertyName) { \
            this->m##PropertyName = value; \
            Q_EMIT propertyName##Changed(); \
        } \
    }

// 定义 ini 配置的 key 属性：type 变量类型，propertyName QObject属性，defaultValue 默认值
// 配置文件 key 名用大写的 PropertyName 字符串
#define CONFIG_PROPERTY(type, propertyName, PropertyName, defaultValue) \
    private: \
    Q_PROPERTY(type propertyName READ propertyName WRITE set##PropertyName NOTIFY propertyName##Changed) \
    public: \
    type propertyName() const { \
        auto &&settings = this->config->configSettings(this->module); \
        settings->beginGroup(group); \
        auto var = settings->value(#PropertyName, defaultValue); \
        settings->endGroup(); \
        return var.value<type>(); \
    } \
    void set##PropertyName(const type &value) { \
        auto &&settings = this->config->configSettings(this->module); \
        settings->beginGroup(group); \
        auto var = settings->value(#PropertyName); \
        if (!var.isValid() || var.value<type>() != value) { \
            settings->setValue(#PropertyName, value); \
            settings->endGroup(); \
            Q_EMIT propertyName##Changed(value); \
        }else{ \
            settings->endGroup(); \
        } \
    } \
    Q_SIGNAL void propertyName##Changed(const type &value); \
    Q_SLOT bool propertyName##Exists() const { \
        auto &&settings = this->config->configSettings(this->module); \
        settings->beginGroup(group); \
        const bool exists = settings->contains(#PropertyName); \
        settings->endGroup(); \
        return exists; \
    }

// 组织名
#define MP_ORG_NAME "MyPhotosGroup"
// 域名-唯一标识
#define MP_ORG_DOMAIN "myphotos.org"
// 主程序名
#define MP_APP_NAME "MyPhotos"
// 主程序版本
#define MP_APP_VERSION "1.00.00"
