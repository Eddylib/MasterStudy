# CMake

此目录专门记录使用CMake的心得。CMake官方网址：https://cmake.org
 

find_package
------------
此命令加载一个外部工程（一般用途就是去加载一个完整的库），在make时指定头文件和lib文件。
此命令有两个模式Module和Config模式。前者是简单的使用方法。后者可以提供更多的定义。

`Module使用方法：`
```
find_package(<package> [version] [EXACT] [QUIET] [MODULE]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])
```

* EXACT: 版本必须匹配。
* QUIET：不显示消息。
* REQUIRED：如果未找到信息，停止cmake过程。
* COMPONENTS：指定组件，得看目标库是否支持。

`Config使用方法：`
```
find_package(<package> [version] [EXACT] [QUIET]
             [REQUIRED] [[COMPONENTS] [components...]]
             [CONFIG|NO_MODULE]
             [NO_POLICY_SCOPE]
             [NAMES name1 [name2 ...]]
             [CONFIGS config1 [config2 ...]]
             [HINTS path1 [path2 ... ]]
             [PATHS path1 [path2 ... ]]
             [PATH_SUFFIXES suffix1 [suffix2 ...]]
             [NO_DEFAULT_PATH]
             [NO_CMAKE_ENVIRONMENT_PATH]
             [NO_CMAKE_PATH]
             [NO_SYSTEM_ENVIRONMENT_PATH]
             [NO_CMAKE_PACKAGE_REGISTRY]
             [NO_CMAKE_BUILDS_PATH] # Deprecated; does nothing.
             [NO_CMAKE_SYSTEM_PATH]
             [NO_CMAKE_SYSTEM_PACKAGE_REGISTRY]
             [CMAKE_FIND_ROOT_PATH_BOTH |
              ONLY_CMAKE_FIND_ROOT_PATH |
              NO_CMAKE_FIND_ROOT_PATH])
```

`两个模式的使用方法和转换关系：`
* 在第一个模式的使用方法下，进入Module过程。
CMake此时将在CMAKE_MODULE_PATH下寻找Find\<package>.cmake，
但似乎在CMakeLists.txt所在目录下的cmake_modules目录下也会去找该文件。
如果找到，这个文件将被读取并且处理。它被用来找到这个库，检查版本，产生需要的信息。
* 在第一个模式下如果没有找到，就进入Config模式。

`CONFIG模式详细使用方法：`

Config模式下，CMake试图去定位一个配置文件。过程下面会提到。名字由下列过程定义：
* 默认情况下寻找<package>Config.cmake或者<package>-config.cmake
* 如果NAME选项被设置，CMake就去寻找<name>Config.cmake或者<name小写>-config.cmake。
注意，如果设置多个name，那么CMake会挨个寻找直到找到为止。
* 如果前面没找到还可以定义CONFIGS。

如果找到了配置文件，配置文件的全路径会被存储在\<package>_CONFIG变量里。
当然，亦可以在CMAKE_CURRENT_LIST_FILE变量中找到相同信息。

`寻找的目录`

首先，CMake会在\<package>_DIR中寻找。
如果找不到，CMake会建立一大堆`prefix`并且在每个`prefix`下的下列目录中进行查找。
W是在Windows下的查找路径，U为Unix，A为Apple。注意，Unix下是不在`prefix`下直接查找的。
这是可以解释的：到了这一步说明\<package>_DIR没有被指定，此时`prefix`已经是通用目录了。
直接在通用目录下放置config文件显然是不合理的。当然Windows还是加了上去。
```
<prefix>/                                                       (W)
<prefix>/(cmake|CMake)/                                         (W)
<prefix>/<name>*/                                               (W)
<prefix>/<name>*/(cmake|CMake)/                                 (W)
<prefix>/(lib/<arch>|lib|share)/cmake/<name>*/                  (U)
<prefix>/(lib/<arch>|lib|share)/<name>*/                        (U)
<prefix>/(lib/<arch>|lib|share)/<name>*/(cmake|CMake)/          (U)
<prefix>/<name>*/(lib/<arch>|lib|share)/cmake/<name>*/          (W/U)
<prefix>/<name>*/(lib/<arch>|lib|share)/<name>*/                (W/U)
<prefix>/<name>*/(lib/<arch>|lib|share)/<name>*/(cmake|CMake)/  (W/U)
<prefix>/<name>.framework/Resources/                    (A)
<prefix>/<name>.framework/Resources/CMake/              (A)
<prefix>/<name>.framework/Versions/*/Resources/         (A)
<prefix>/<name>.framework/Versions/*/Resources/CMake/   (A)
<prefix>/<name>.app/Contents/Resources/                 (A)
<prefix>/<name>.app/Contents/Resources/CMake/           (A)
```
`prefix`的创建：
如果NO_DEFAULT_PATH选项在find_package命令里被声明，所有NO_*的命令都会被启用。

1、CMake专属的缓存变量，可在命令行里使用-D\<var>=value来改变
（可在CMakeLists.txt中改变）。
如果NO_CMAKE_PATH被设置，此过程跳过。
```cmake
CMAKE_PREFIX_PATH
CMAKE_FRAMEWORK_PATH
CMAKE_APPBUNDLE_PATH
```
2、CMake专属的系统环境变量。
可由用户的shell来配置。如果NO_CMAKE_ENVIROMENT_PATH被设置，此步跳过。
```cmake
<package>_DIR #注意，这里的<package>_DIR指的是系统环境变量，而不是CMakeLists.txt中说明的变量
CMAKE_PREFIX_PATH
CMAKE_FRAMEWORK_PATH
CMAKE_APPBUNDLE_PATH
```
3、被HINTS选项声明的位置。

4、系统环境变量`PATH`中声明的位置，如果其中的目录以bin或者sbin结尾，位置会自动地被转换为其父目录。
如果NO_SYSTEM_ENVIROMENT_PATH被设置，此过程跳过。

5、在CMake的User Package Registry中寻找。
关于这个东西的具体定义下面会总结。这个步骤可以通过设置NO_CMAKE_PACKAGE_REGISTRY、
或者CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY被设置为TRUE，来跳过。

6、查找为当前系统平台专门定义的文件，里面设置的变量（下面列出）。这个过程可以通过设置NO_CMAKE_SYSTEM_PATH来跳过。
```cmake
CMAKE_SYSTEM_PREFIX_PATH
CMAKE_SYSTEM_FRAMEWORK_PATH
CMAKE_SYSTEM_APPBUNDLE_PATH
```

7、在CMake的System Package Registry中寻找。
关于这个东西的具体定义下面会总结。这个步骤可以通过设置NO_CMAKE_SYSTEM_PACKAGE_REGISTRY、
或者CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY被设置为TRUE，来跳过。

8、被PATH选项声明的位置。

9、CMAKE_FIND_ROOT_PATH，CMAKE_SYSROOT。
这两个变量在交叉编译时非常有用。常用的情况就是将他们指向目标平台的根目录。
这两个变量可以重定义查找的根目录。
所以他们会影响其他地方。他们的行为可以通过以下的变量来设置。
* 默认情况下，CMAKE_FIND_ROOT_PATH变量下的目录被查找。然后CMAKE_SYSROOT。
最后在真正的系统根目录下查找。
* CMAKE_FIND_ROOT_PATH_BOTH选项被设置即是默认设置。
* NO_CMAKE_FIND_ROOT_PATH不使用CMAKE_FIND_ROOT_PATH变量。
* ONLY_CMAKE_FIND_ROOT_PATH。
只在重定位的根目录和CMAKE_STAGING_PRIFIX的目录下查找。

`User|System Package Registry`
目前没什么用。

`总结`
* 库的cmake文件分两大类，一类是Find\<package>.cmake。
这类被首先搜索，搜索顺序是：CMAKE_MODULE_PATH-->\<CMAKE_ROOT>/share/cmake-x.y/Modules/。官方文档上这么说，但是