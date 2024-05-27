# PostgreSQL Tuner

## 概述

PostgreSQL Tuner 是一个基于C语言编写的调优工具，用于收集PostgreSQL数据库的性能数据和SQL执行信息，生成调优建议。该工具旨在帮助数据库管理员识别性能瓶颈并提供相应的优化建议。

## 功能

- 收集PostgreSQL数据库的性能数据
- 分析SQL语句的执行信息
- 生成针对数据库和SQL语句的调优建议

## 使用步骤

### 1. 克隆项目

```bash
git clone https://github.com/kinlon/pg-tuner.git
cd pg-tuner
```
### 2. 克隆项目
确保已安装PostgreSQL开发库（libpq-dev）
```bash
make
```
### 3. 配置数据库连接

```bash
DB_NAME=your_db
DB_USER=your_user
DB_PASSWORD=your_password
DB_HOST=your_host
DB_PORT=5432
```
### 4. 运行项目

```bash
./pg_tuner config.cfg
```
### 5. 查看调优建议

项目运行后会输出调优建议，帮助您优化数据库性能。

### 贡献

欢迎贡献代码和建议，请提交pull request或issue。

### 许可证

本项目采用Apache 2.0许可证。
