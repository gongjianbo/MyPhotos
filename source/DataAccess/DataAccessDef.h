#pragma once
#include <QObject>

// 文件信息数据结构
struct FileInfo
{
    Q_GADGET
    Q_PROPERTY(qint64 id MEMBER id)
    Q_PROPERTY(QString fileName MEMBER fileName)
    Q_PROPERTY(QString suffix MEMBER suffix)
    Q_PROPERTY(qint64 size MEMBER size)
    Q_PROPERTY(qint64 createTime MEMBER createTime)
    Q_PROPERTY(qint64 importTime MEMBER importTime)
    Q_PROPERTY(qint64 modifyTime MEMBER modifyTime)
    Q_PROPERTY(int type MEMBER type)
    Q_PROPERTY(QString comment MEMBER comment)
    Q_PROPERTY(QString folder MEMBER folder)
    Q_PROPERTY(qint64 sourceId MEMBER sourceId)
    Q_PROPERTY(QString sourcePath MEMBER sourcePath)
public:
    enum FileType : char {
        NoneType = 0, // 未识别的类型
        ImageType, // 静态图片，jpg/png/bmp等
    };
    Q_ENUM(FileType)
public:
    // 文件信息id-从1开始自增，同时也是文件存储名称
    qint64 id{0};
    // 文件名（无后缀），用于展示和导出
    QString fileName;
    // 文件后缀
    QString suffix;
    // 文件字节大小
    qint64 size{0};
    // 创建时间，导入时根据文件创建时间初始化
    qint64 createTime{0};
    // 导入时间
    qint64 importTime{0};
    // 最近修改时间，导入时根据文件修改时间初始化
    qint64 modifyTime{0};
    // 文件分类，FileType枚举
    int type{NoneType};
    // 备注
    QString comment;
    // 存储的分组目录
    QString folder;
    // 源文件id，如果是内部生成的附件需要填充
    qint64 sourceId{0};
    // 源文件路径
    QString sourcePath;

    // 根据id默认值判断是否有效
    Q_INVOKABLE inline bool isValid() const { return (id != 0); }
    // 转为字符串用于打印等
    Q_INVOKABLE QString toString() const;
    // 比较所有字段是否相等
    Q_INVOKABLE bool compare(const FileInfo &other) const;
    // 运算符重载
    bool operator!=(const FileInfo &other) const;
    bool operator==(const FileInfo &other) const;
};
Q_DECLARE_METATYPE(FileInfo)

// 图片信息数据结构
struct ImageInfo
{
    Q_GADGET
    Q_PROPERTY(qint64 id MEMBER id)
    Q_PROPERTY(int width MEMBER width)
    Q_PROPERTY(int height MEMBER height)
    Q_PROPERTY(FileInfo fileInfo MEMBER fileInfo)
public:
    // 图片信息id-从1开始自增
    qint64 id{0};
    // 图片宽
    int width{0};
    // 图片高
    int height{0};
    // 关联的文件信息
    FileInfo fileInfo;

    // 根据id默认值判断是否有效
    Q_INVOKABLE inline bool isValid() const { return (id != 0) && fileInfo.isValid(); }
    // 转为字符串用于打印等
    Q_INVOKABLE QString toString() const;
    // 比较所有字段是否相等
    Q_INVOKABLE bool compare(const ImageInfo &other) const;
    // 运算符重载
    bool operator!=(const ImageInfo &other) const;
    bool operator==(const ImageInfo &other) const;
};
Q_DECLARE_METATYPE(ImageInfo)
