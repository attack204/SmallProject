package com.example.soundwave.network

import com.example.soundwave.datas.MailData
import com.example.soundwave.datas.SoundWaveData
import com.example.soundwave.datas.SoundWaveMessageData
import com.squareup.moshi.Moshi
import com.squareup.moshi.kotlin.reflect.KotlinJsonAdapterFactory
import retrofit2.Retrofit
import retrofit2.converter.moshi.MoshiConverterFactory
import retrofit2.http.GET
import retrofit2.http.Path


private const val BASE_URL = "http://192.168.56.1:3000/api/"

private val moshi = Moshi.Builder()
    .add(KotlinJsonAdapterFactory())
    .build()

private val retrofit = Retrofit.Builder()
    .addConverterFactory(MoshiConverterFactory.create(moshi))
    .baseUrl(BASE_URL)
    .build()


interface SoundWaveApiService {
    @GET("soundwaves/{userId}")
    suspend fun getSoundWaves(): MutableList<SoundWaveData>

    @GET("soundwavemessages/{userId}")
    suspend fun getSoundWaveMessages(@Path("userId") userId: String): MutableList<SoundWaveMessageData>

    @GET("mails/{userId}")
    suspend fun getMails(@Path("userId") userId: String): MutableList<MailData>
}

object SoundWaveApi {
    val retrofitService : SoundWaveApiService by lazy {
        retrofit.create(SoundWaveApiService::class.java)
    }
}