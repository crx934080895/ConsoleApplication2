#include <stdio.h>
#include "UI.h"

void main()
{
    load_users();
    load_planes();
    init();
    main_screen(); //进入主界面
}