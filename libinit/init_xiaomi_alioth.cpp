/*
 * Copyright (C) 2021 Paranoid Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <vector>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

using android::base::GetProperty;

void property_override(char const prop[], char const value[], bool add = true) {
    prop_info* pi;

    pi = (prop_info*)__system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_variant_info(bool hasNfc, char const brandName[], char const marketName[], char const modelName[]) {
    if(hasNfc) {
        property_override("ro.boot.product.hardware.sku", "nfc");
    }
    property_override("ro.product.brand", brandName);
    property_override("ro.product.odm.brand", brandName);
    property_override("ro.product.vendor.brand", brandName);

    property_override("ro.product.marketname", marketName);
    property_override("ro.product.odm.marketname", marketName);
    property_override("ro.product.vendor.marketname", marketName);

    property_override("ro.product.model", modelName);
    property_override("ro.product.odm.model", modelName);
    property_override("ro.product.vendor.model", modelName);

    property_override("ro.product.vendor.manufacturer", "Xiaomi");

    property_override("vendor.usb.product_string", marketName);
    property_override("bluetooth.device.default_name", marketName);
}

void vendor_load_properties() {
    std::string region = GetProperty("ro.boot.hwc", "");
    if (region.find("CN") != std::string::npos) {
        load_variant_info(true, "Redmi", "Redmi K40", "M2012K11AC");
    } else if (region.find("INDIA") != std::string::npos) {
        load_variant_info(false, "Mi", "Mi 11X", "M2012K11AI");
    } else {
        load_variant_info(true, "POCO", "POCO F3", "M2012K11AG");
    }
}