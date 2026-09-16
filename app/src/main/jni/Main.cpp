#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <string>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.hpp"
#include "Menu/Menu.hpp"
#include "Menu/Jni.hpp"
#include "Includes/Macros.h"
#include "dobby.h"

// القائمة المخصصة للتحدي ضد صديقك
jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Toggle_No Recoil (ثبات السلاح)"),
            OBFUSCATE("Toggle_Auto Aimbot (التصويب التلقائي)"),
            OBFUSCATE("Toggle_ESP Box (كشف الأماكن)")
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

bool btnPressed = false;

// استهداف مكتبة اللعبة الأساسية
#define targetLibName OBFUSCATE("libil2cpp.so")

// دالة تفعيل الميزات والتحكم بالذاكرة الحية ديناميكياً
void Changes(JNIEnv *env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jlong Lvalue, jboolean boolean, jstring text) {

    switch (featNum) {
        case 0: // ميزة ثبات السلاح (No Recoil)
            // استغلال البنية التحتية للمشروع لتعديل الدالة بالاسم مباشرة (Symbol) بدلاً من الـ Offset
            // الكود البرمجي "mov x0, #0; ret" يقوم بتصفير قيمة الارتداد تماماً بمجرد التفعيل
            PATCH_SWITCH(targetLibName, "WeaponModel$$get_Recoil", "mov x0, #0; ret", boolean);
            break;

        case 1: // ميزة التصويب التلقائي (Auto Aimbot)
            // نقوم بحقن قيمة True (رقم 1) داخل دالة الـ AimAssist لتلتصق الطلقات تلقائياً بالخصم
            PATCH_SWITCH(targetLibName, "WeaponModel$$get_IsAimAssist", "mov x0, #1; ret", boolean);
            break;

        case 2: 
            if (boolean) {
          
                
            }
            break;
    }
}
