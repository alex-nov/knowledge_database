### knowledge_database - KD

App for save and cataloge diffrent knowledge

It'll be good make app client-server via websockets and REST Api

## Архитектура:
+ logical core - work with DB, create ContentPage and send it
+ console interface - show ContentPage, create new text ContentUnit, edit ContentUnit
+ Qt UI - show ContentPage with text, video/animation
+ web view - same as Qt UI, but in browser

## TODO:
+ Базовая версия KD
    - [x] Базовую логику движка -создание юнитов, сохранение в/загрузка из БД; навигация по юнитам
    - [ ] Добавить библиотеку для работы с json - все страницы конвертировать в удобный json
    - [ ] Добавить библиотеку websockets - преобразовать приложение в сервер
    - [ ] Создать десктоп клиент на QT и консольный для тестирования
    - [ ] web клиент для просмотра базы в браузере
+ Расширенная версия(мб форк)
    - [ ] Добавить авторизацию
    - [ ] Переход на тред-пулы для запросов сети и обращения к БД(высонагруженный сервис)
    - [ ] Роли - пользователь, модер, админ с соотв. правами и функциями

## Сторонние зависимости
+ [библиотека fmt](https://github.com/fmtlib/fmt)
+ [библиотека pqxx](https://github.com/jtv/libpqxx)
+ для  unit-тестирования [библиотека googletest](https://github.com/google/googletest)

## Сборка и запуск проекта
1. Установить зависимости:
```
sudo apt install -y libboost-dev postgresql
```

2. Настроить базу для работы:
```
CREATE DATABASE knowledge;
CREATE USER know
ALTER USER know WITH PASSWORD 'know';
GRANT CREATE ON DATABASE knowledge TO know;
```

3. Аналогично сделать базу для тестов:
```
CREATE DATABASE kd_test;
CREATE USER kd_test
ALTER USER kd_test WITH PASSWORD 'kd_test';
GRANT CREATE ON DATABASE kd_test TO kd_test;
```

4. Запустить скрипт сборки
```
./build
```

5. ... profit!


