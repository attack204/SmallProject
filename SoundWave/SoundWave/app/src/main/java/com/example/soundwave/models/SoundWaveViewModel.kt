package com.example.soundwave.models

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.soundwave.datas.SoundWaveData
import com.example.soundwave.network.SoundWaveApi
import kotlinx.coroutines.launch


class SoundWaveViewModel : ViewModel() {

    private val _soundWaveList = MutableLiveData<MutableList<SoundWaveData>>()
    val soundWaveList: LiveData<MutableList<SoundWaveData>> = _soundWaveList

    init {
        getSoundWaveList()
    }

    // 按用户userId获取他的音波
    private fun getSoundWaveList() {
        viewModelScope.launch {
            _soundWaveList.value = SoundWaveApi.retrofitService.getSoundWaves()
        }
    }
}