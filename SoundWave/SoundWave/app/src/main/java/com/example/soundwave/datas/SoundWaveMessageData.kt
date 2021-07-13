package com.example.soundwave.datas

import com.squareup.moshi.Json


data class SoundWaveMessageData(
    @Json(name = "_id") val id: String,
    @Json(name = "content") val content: String,
    @Json(name = "userId") val userId: String
)
