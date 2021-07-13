package com.example.soundwave.models

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.soundwave.datas.MailData
import com.example.soundwave.network.SoundWaveApi
import kotlinx.coroutines.launch


class MailViewModel : ViewModel() {

    private val _mailList = MutableLiveData<MutableList<MailData>>()
    val mailList: LiveData<MutableList<MailData>> = _mailList

    init {
        getMailList("60dd7597f5465154f40e022e")
    }

    // 按用户userId获取他的音讯
    private fun getMailList(userId: String) {
        viewModelScope.launch {
            _mailList.value = SoundWaveApi.retrofitService.getMails(userId)
        }
    }
}