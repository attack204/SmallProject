package com.example.soundwave.datas

import com.squareup.moshi.Json


data class SoundWaveData(
    @Json(name = "_id") val id: String,
    @Json(name = "soundWaveName") val soundWaveName: String,
    @Json(name = "userId") val userId: String
)
