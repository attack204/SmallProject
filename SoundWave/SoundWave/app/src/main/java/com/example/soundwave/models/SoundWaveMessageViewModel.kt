package com.example.soundwave.models

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.soundwave.datas.SoundWaveMessageData
import com.example.soundwave.network.SoundWaveApi
import kotlinx.coroutines.launch


class SoundWaveMessageViewModel : ViewModel() {

    private val _soundWaveMessageList = MutableLiveData<MutableList<SoundWaveMessageData>>()
    val soundWaveMessageList: LiveData<MutableList<SoundWaveMessageData>> = _soundWaveMessageList

    init {
        getSoundWaveMessageList("60dd7597f5465154f40e022e")
    }

    // 按用户userId获取他的音波消息
    private fun getSoundWaveMessageList(userId: String) {
        viewModelScope.launch {
            _soundWaveMessageList.value = SoundWaveApi.retrofitService.getSoundWaveMessages(userId)
        }
    }
}