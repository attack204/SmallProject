package com.example.soundwave.bindingadapters

import androidx.databinding.BindingAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.soundwave.adapters.SoundWaveMessageAdapter
import com.example.soundwave.datas.SoundWaveMessageData


@BindingAdapter("soundWaveMessageListData")
fun bindRecyclerView(recyclerView: RecyclerView, data: MutableList<SoundWaveMessageData>?) {
    val adapter = recyclerView.adapter as SoundWaveMessageAdapter
    adapter.submitList(data)
}