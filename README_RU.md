<div align="center">
  <a href="https://github.com/One-Core-API/One-Core-API/releases">
    <img src="Assets/banner.png" width="100%" height="auto" alt="Banner">
  </a>
  <h6>Большое спасибо @pashtetusss777 за баннер</h6>
</div>

---

**Язык:**
[English](README.md) | [简体中文](README_CN.md) | [Русский](README_RU.md) | [Українська](README_UK.md) | [日本語](README_JP.md) | [Português-Brasil](README_BR.md)

---

**Этот репозиторий содержит бинарные релизы проекта One-Core-API. Они совместимы с Windows Server 2003 RTM, SP1 и SP2, Windows XP RTM, SP1, SP2 и SP3 и Windows XP x64 SP1/SP2. Однако, настоятельно рекомендуется использовать систему с последним пакетом обновлений и всеми доступными обновлениями.**

- [Основные возможности](#основные-возможности)
  - [Перед использованием этого программного обеспечения](#перед-использованием-этого-программного-обеспечения)
- [Как установить One-Core-API?](#как-установить-one-core-api)
- [Как удалить One-Core-API?](#как-удалить-one-core-api)
- [Совместимость приложений](#совместимость-приложений)
- [Известные ограничения](#известные-ограничения)
- [Перед тем, как сообщить о проблеме...](#перед-тем-как-сообщить-о-проблеме)
- [Структура репозитория](#структура-репозитория)
- [Дополнительная информация и ссылки](#дополнительная-информация-и-ссылки)
  - [Официальный сервер Discord](#официальный-сервер-discord)
- [Демонстрация / Подтверждение концепции](#демонстрация--подтверждение-концепции)

## Основные возможности

- **Увеличение поддержки памяти до 128 ГБ для x86 и 2 ТБ для x64 по умолчанию;**
- **Позволяет поддержку запуска новых программ, разработанных для современных ОС Windows;**
- **Позволяет поддержку нового оборудования с новыми драйверами контроллеров;**
- **Многоязычная поддержка для всех поддерживаемых языков Windows XP и Windows Server 2003;**

### Перед использованием этого программного обеспечения

> Это программное обеспечение использует модифицированные файлы из соответствующих систем, а также включает файлы, которые все еще находятся на стадии тестирования или экспериментирования, и **разрабатывается одним человеком**. Следовательно, предсказать все возможные сценарии для различных конфигураций компьютеров или виртуальных машин невозможно.
>
> <h4>Переход между Windows XP/2003 и Vista ознаменовал значительный скачок в разработке новых API, технологий и модификаций существующих API. Это затрудняет достижение такого же уровня совместимости между системами NT 5.x и NT 6.x.</h4>
>
> Я прошу вас сохранять спокойствие и осторожность.
> Прежде чем сделать вывод, что программное обеспечение имеет недостатки или "плохое качество", **пожалуйста, сообщите о любых проблемах, с которыми вы столкнулись, через Github Issues или [сервер Discord](https://discord.gg/eRcGuFtn6p)**.
>
> Обратите внимание, что я не могу гарантировать, что все проблемы будут решены. Однако я их проанализирую и приложу все усилия, чтобы их исправить.
>
> Ваша помощь ценна, а жалобы или негативные отзывы не способствуют улучшению продукта.

## Как установить One-Core-API?

One-Core-API использует технологию установки исправлений (hotfixes), которая использовалась до Windows NT 5.x. Благодаря этому вы заметите, что она очень похожа на установку пакета обновлений. Вам нужно перейти в раздел [Releases](https://github.com/Shorthorn-Project/One-Core-API-Binaries/releases), выбрать версию, которую вы хотите протестировать, и скачать zip-файл. После загрузки распакуйте файл, и вы увидите, что есть две папки, по одной для каждой поддерживаемой платформы: x64 и x86. Внутри каждой папки будет исполняемый файл с названием: One-Core-API-Pack.exe. Дважды щелкните по этому файлу и выполните шаги установки, которые в основном сводятся к: "Далее, выбрать принять лицензию, Далее и Готово". Это так просто.

<details>
  <summary>Пошаговое руководство с изображениями</summary>

  **Загрузка:**

  ![image](https://github.com/user-attachments/assets/09322142-2655-47d2-9723-26fe6fb67494)

  **Распаковка:**
  ![image](https://github.com/user-attachments/assets/7fbba140-5a87-45b3-bec0-a5236a676b04)

  **Откройте распакованное содержимое и выберите свою архитектуру. Если на баннере нет x64, это x86:**
  ![image](https://github.com/user-attachments/assets/6bdd8a39-9aac-4ee1-88fd-9fda4db144ea)

  **Дважды щелкните по исполняемому файлу:**
  ![image](https://github.com/user-attachments/assets/e5e03ff2-4de5-475a-bbd8-755df687b187)

  **Далее:**
  ![image](https://github.com/user-attachments/assets/2fd62bd9-b1a8-4e1d-8769-92b9bbcf2a6b)

  **Принять и Далее:**
  ![image](https://github.com/user-attachments/assets/ca62c9a2-9995-45cd-929e-b7613f9b389e)

  **Подождите:**
  ![image](https://github.com/user-attachments/assets/06b6fa4c-67dd-4149-9b97-bdee52c60bdb)

  **Готово и наслаждайтесь!**
  ![image](https://github.com/user-attachments/assets/8210f667-5f51-4d36-a4a5-7b5a4f24b278)

</details>

## Как удалить One-Core-API?

Как упоминалось, One-Core-API использует технологию установки исправлений (hotfixes), которая использовалась в Windows NT до версии 5.x. Поэтому, чтобы удалить его, необходимо перейти в Панель управления -> "Установка/Удаление программ" и выбрать опцию "Показать обновления". После выбора этой опции отобразятся другие обновления (если они установлены), включая One-Core-API. Прокрутите страницу вниз, пока не отобразится One-Core-API, и нажмите на него. Появится кнопка "Удалить". Нажмите на кнопку и выполните шаги удаления (в основном, Далее->Готово).

<details>
  <summary>Пошаговое руководство с изображениями</summary>

  **Перейдите в Панель управления:**
  ![image](https://github.com/user-attachments/assets/ceaf9dc2-135c-4f6b-8b22-ce5eb3f8d421)

  **Нажмите на Установка/Удаление программ:**
  ![image](https://github.com/user-attachments/assets/b0d6406a-db6b-4ca8-b2b9-cc020df17950)

  **Отметьте "Показать обновления":**
  ![image](https://github.com/user-attachments/assets/83bdef02-9704-4e77-a0b0-cba70a4de80a)

  **Обновление появится. Прокрутите вниз, пока не появится One-Core-API:**
  ![image](https://github.com/user-attachments/assets/2ff6137f-b621-4dff-9516-b45f83c3a013)

  **Нажмите на One-Core-API Pack, а затем на кнопку "Удалить":**
  ![image](https://github.com/user-attachments/assets/c66909ae-2e3a-4871-a320-e60c66210db9)

  **Появится окно удаления. Нажмите "Далее":**
  ![image](https://github.com/user-attachments/assets/71343989-6e16-48b4-982d-173a4b15774d)

  **Подождите:**
  [image](https://github.com/user-attachments/assets/01401f4f-e4be-4e8a-82d2-3480f143fedd)

  **Нажмите "Готово", и Windows перезагрузится:**
  ![image](https://github.com/user-attachments/assets/b6f06465-786f-4503-b71b-30e9224ad9fc)

</details>

## Совместимость приложений

<details>
  <summary>Браузеры и почтовые клиенты</summary>

- Браузеры на основе Chromium (Chrome, Opera, Edge и другие) до последней версии
- Установщик Chrome до версии 109 (версия для Windows 10 пока не поддерживается)
- Браузеры на основе Gecko (Firefox, Zen Browser) до последних версий (однако YouTube работает только до версии Firefox 130);
- Seamonkey до версии 2.53.10;
- Maxthon до версии 7.1.6;
- Vivaldi до последней версии;
- Epic Browser 120
- Thunderbird до последней версии
</details>

<details>
  <summary>Мессенджеры и другие программы для общения</summary>

- Discord 0.309.0;
- Legocord (форк Discord) последняя версия;
- Telegram Desktop;
- Line;
- Zoom;
- Filezilla (последняя версия);
- TeamViewer 14
</details>

<details>
  <summary>Офисные приложения</summary>

- LibreOffice 24.0.x (последняя версия);
- Adobe Reader DC (до 2024 года);
- Foxit PDF Reader (2023 год)
</details>

<details>
  <summary>IDE и языки программирования</summary>

- IDE от JetBrains до последних релизов (2024);
- Visual Studio 2012 и Visual Studio 2013;
- Eclipse IDE до последней версии;
- Visual Studio Code (и форки, такие как Codium) до последней версии;
- Android Studio до последней версии;
- NetBeans до последней версии;
- Python 3.6 (3.8/3.9 также могут работать, только [модифицированная](https://mega.nz/folder/KxExlAiC#L9rAQ5kTCtlHgZUwaxMpgw) версия)
</details>

<details>
  <summary>Java</summary>

- Java JDK и альтернативные JDK или OpenJDK до версии 24 (возможно, другие версии также работают). Скачать можно здесь: https://bell-sw.com/pages/downloads/#/java-11-lts;
- JDK 1.8 (пока только для Windows XP x64)
</details>

<details>
  <summary>Встроенные приложения из Windows Vista/7</summary>

- Игры из Windows 7;
- Paint из Windows 7;
- Wordpad из Windows 7;
- Встроенные приложения из Windows Vista
</details>

<details>

  <summary>Игры с поддержкой OpenGL, DirectX 9EX, 10 и 11</summary>

- Need for Speed Most Wanted 2012;
- Need for Speed The Run;
- Street Fighter V;
- Injustice: Gods Among Us;
- Assassin's Creed Black Flag;
- Crysis 1, 2 и 3 (режим DirectX 10-11);
- GTA Trilogy Definitive Edition;
- GTA V;
- Minecraft 1.21.x
- Resident Evil 5 (режим DX10);
- Lost Planet;
- Far Cry 4;
- Far Cry Primal;
- Tropico 5;
- Metro Last Night;
- Cuphead;
- Horizon Turbo
</details>

<details>
  <summary>Другое</summary>

- Продукты Adobe (Photoshop, Illustrator, Dreamweaver и т.д.) до версии 2019 года;
- .Net Framework до 4.8;
- .NET 6.0
- Geekbench 4.2;
- Performance Test;
- Spotify для Windows 7 и для Windows 10;
- Node 10.24;
- Winrar 7.0 (последняя версия);
- Postman
- Dbeaver
- Kate 23.08.1
</details>

## Известные ограничения

- Youtube в Firefox, начиная с версии 131, не работает. Поэтому рекомендуется использовать версию 115 или 128 ESR.
- Некоторые установщики приложений могут не работать, например, electron based приложения (MS teams), Office 2013 или GIMP 3.0 RC2 и т.д., аварийно завершаются и приложение не устанавливается. Некоторые установщики и программы требуют поддержки AVX операционной системой, что не поддерживается вовсе. Поэтому используйте предварительно установленную версию, скопированную из другой операционной системы;
- Пакеты нельзя интегрировать через nlite в ISO Windows, так как используется инструмент под названием "SFXCAB Substitute", а не стандартная версия от Microsoft;
- Стандартные установщики .Net Framework, начиная с 4.6, не поддерживаются на данный момент. Вам нужна перепакованная версия, как сделано здесь: https://github.com/abbodi1406/dotNetFx4xW7. И доступно здесь: https://www.wincert.net/forum/topic/13805-microsoft-net-framework-472-full-x86x64-incl-language-packs-by-ricktendo/#comment-123251. Другие версии также доступны, ищите в темах форума;
- Новые версии palemoon могут столкнуться с проблемой ошибки параллельной конфигурации;
- Opera 39-50 может потребовать следующих параметров для запуска: --disable-gpu (чтобы предотвратить черный экран) и --single-process (чтобы предотвратить вечную загрузку первой страницы);

## Перед тем, как сообщить о проблеме...

**Прежде чем сообщать о проблеме, я настоятельно рекомендую проверить, существует ли проблема в [One-Core-API-Canary](https://github.com/shorthorn-project/One-Core-API-Binaries-Canary) и внимательно просмотреть существующие [проблемы](https://github.com/Skulltrail192/One-Core-API-Binaries/issues), чтобы проверить, сообщалось ли о вашей проблеме.**

**Если проблема _существует_ в Canary и еще не указана в текущих проблемах, пожалуйста, предоставьте подробный отчет о вашей проблеме, включая следующую информацию:**

**1. Конфигурация системы:**

- **Тип** (ПК/ВМ)
- **Редакция ОС Windows** (например, Windows XP Professional Service Pack 3)
- **Обновления после SP:**
  - Были ли установлены обновления после Service Pack обновлений? (Да/Нет)
    - Если да, укажите, были ли они установлены **до** или **после** установки One-Core-API.
- **Установленное программное обеспечение:** Перечислите любое соответствующее программное обеспечение, которое может быть связано с проблемой (например, Adobe Photoshop CC 2018, Firefox 132 и т. д.).
- **Технические характеристики**:
  - **Если физическое оборудование:** Предоставьте подробности о процессоре, ОЗУ (тип, объем), типе жесткого диска и его емкости (например, диск IDE, 120 ГБ).
  - **Если виртуальная машина:** Укажите детали конфигурации виртуальной машины (например, Oracle VirtualBox 6.1.0, 2 ГБ ОЗУ, диск 120 ГБ, режим AHCI).
- **Шаги для воспроизведения ошибки**

> **ВАЖНО:** Если возможно, пожалуйста, также **добавьте любые соответствующие журналы** к обращению. Это значительно поможет быстрее идентифицировать решение.

> Также целесообразно добавить видеозапись проблемы, если это возможно.
>
> **Обратите внимание, что обращение будет закрыто, если проблему нельзя воспроизвести.**

## Структура репозитория

- Documents: Документация проекта, известные ошибки, использование sfxcab (для создания установщиков) и т.д.
- Packages\x86 и Packages\x64: Бинарные выпуски, сгруппированные по пакетам. Вы можете загрузить и установить/обновить пакеты непосредственно отсюда (то есть, перейдя к Packages\x86\Base installer\update и запустив update.exe).
- Todo: Задачи для выполнения
- Test: Некоторые бинарные файлы и документы для тестирования;
- Release: Скрипты для создания нового бинарного выпуска;
- Output: Выходные бинарные файлы, которые можно сгенерировать с помощью скриптов в папке Release;

## Дополнительная информация и ссылки

**Расширенные возможности для систем на основе One-Core-API:**

<b><a href="https://github.com/shorthorn-project/One-Core-API-Extras" style="font-size: 18px">https://github.com/shorthorn-project/One-Core-API-Extras</a></b>

**Инструменты для новой системы развертывания для систем на основе One-Core-API:**

<b><a href="https://github.com/Skulltrail192/One-Core-API-Tools" style="font-size: 18px">https://github.com/Skulltrail192/One-Core-API-Tools</a></b>

### Официальный сервер Discord

**Если вы хотите присоединиться к нашему официальному серверу Discord One-Core-API, вы можете присоединиться здесь:**

<b><a href="https://discord.gg/eRcGuFtn6p" style="font-size: 25px">https://discord.gg/eRcGuFtn6p</a></b></n>

## Демонстрация / Подтверждение концепции

Несколько скриншотов приложений, работающих на XP/Server 2003:

<details>
  <summary>Браузеры и Thunderbird</summary>

**Chrome 132**
![image](https://github.com/user-attachments/assets/84e83d53-ea8e-47b9-a566-e0986c91b812)

**Edge 134 (предварительная версия для разработчиков)**
![image](https://github.com/user-attachments/assets/f0b6a47c-dc37-45b0-beaf-c85002e37386)

**Opera 116**
![image](https://github.com/user-attachments/assets/ee962193-8de6-458e-8d35-769638e9fbde)

**Firefox 122**
![Firefox122](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/db647daf-0960-4ace-ad2f-63469dbf3881)

**Thunderbird 132**
![image](https://github.com/user-attachments/assets/1ccdd59f-849a-4f1c-86e0-bcc9e1ce02e2)

**Basilisk**
![image_2022_04_08T21_38_17_976Z](https://user-images.githubusercontent.com/5159776/178077859-079bfca4-bdb6-402e-8991-b88e7dfe387c.png)

**Vivaldi**
![image](https://github.com/user-attachments/assets/580966ab-f170-42a9-9f9d-3c15fe2ec8b2)

</details>

<details>
  <summary>Игры</summary>

**Microsoft Chess 3D**
![Chess3d](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/bd1ad0c6-edde-4ff2-a6e0-074c7379fab6)

**Minecraft 1.21**
![image](https://github.com/user-attachments/assets/cfd05f13-617e-49a0-b416-67906d42840b)

</details>

<details>
  <summary>Мессенджеры и другие программы для общения</summary>

**Telegram 4.14**
![Telegram-Desktop](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/73e13167-49b8-4282-81cb-969435046dde)

**Discord 0.309**
![Discord-Login](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/8a4c12b5-19fc-454d-b02a-a1db807d3900)
![Discord](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/eb673541-4e66-4c76-867e-346edbaaa0af)

**Telegram Desktop**
![Telegram-Desktop](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/d23b9add-629d-45a3-a8e1-c331271bc0d3)

**Конференция Zoom**
![Zoom](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/d002cf1b-c5f4-4c0c-b629-00e031a56765)

</details>

<details>
  <summary>Встроенные приложения Windows 7</summary>

**Записки Windows 7**
![StickyNotes](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/669ba3e4-b831-4a96-ad40-d87e3e9531e2)

**Paint Windows 7**
![Paint](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/81728a44-c9e7-41e8-b68b-8ea7b119ebba)

**Wordpad Windows 7**
![Wordpad](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/9dac02c7-7139-47fe-8732-ccd9ef91090b)

</details>

<details>
  <summary>Другое</summary>

**Spotify (для Windows 7)**
![Spotify-Windows7](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/09de7c20-8670-45dc-9471-a6db9349abd0)

**Visual Studio Code 1.81**
![VisualCode](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/b21748b9-25bb-412d-95b3-2219d2efdf42)

**LibreOffice 24 (последняя)**
![LibreOffice](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/11fd191d-270c-428d-8d41-0498e8fafb3b)
![Writer-LibreOffice](https://github.com/Skulltrail192/One-Core-API-Binaries/assets/5159776/e389a39b-febd-45f6-9c6f-25f64e460142)

**Java 11**
![Capturar](https://user-images.githubusercontent.com/5159776/178078132-da504607-a1ca-4f8d-ae25-6a7eb367bdaa.PNG)

**Avast и Chromium 68**
![Avast](https://user-images.githubusercontent.com/5159776/178078208-c13b3448-ee6a-4c56-9d94-d0c62d51949e.PNG)

</details>
