CrossProcessNotificationManager
===============================

跨进程消息服务 —— 使用内存映射文件方式

该消息服务框架使用一个独立Server进程创建并管理用于交换数据的 file-mapping kernel object（内存映射文件），
使用跨进程消息交换的程序按照约定token将对应的内存映射文件映射到自身的地址空间中，该内存映射文件将作为与
Server交换数据的信道，Server则将消息内容转储到目标程序使用的内存映射文件上

依赖库：Qt40
