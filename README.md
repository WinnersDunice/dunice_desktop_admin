
# Панель привязки пользователя к компьютеру
Служит для инициализации компьютера и привязки его к пользователю.\
Для полной работы необходимо установить [этот](https://github.com/WinnersDunice/dunice_desktop) проект - клиентское приложение.
## Использование

На флеш накопителе необходимо создать 2 папки:
```
├── Admin
└── Viewer
```
также рядом с ними необходимо установить [файл установки](https://github.com/WinnersDunice/dunice_desktop_admin/blob/main/Install.bat).\
В папку ``Admin`` поместить файлы из ``./release``\
В папку ``Viewer`` поместить файлы из ``./release`` [этого](https://github.com/WinnersDunice/dunice_desktop) репозитория.\
При запуске ``Install.bat`` будет создана папка ``C:\Viewer``, в которую переместится и запустится клиентская часть. Также будет запущена клиентская часть из ``Viewer``. Подробнее о клиентской части [здесь](https://github.com/WinnersDunice/dunice_desktop/blob/main/README.md).



