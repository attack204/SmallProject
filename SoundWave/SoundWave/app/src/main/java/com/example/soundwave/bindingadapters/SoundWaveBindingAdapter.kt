package com.example.soundwave.bindingadapters

import androidx.databinding.BindingAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.soundwave.adapters.SoundWaveAdapter
import com.example.soundwave.datas.SoundWaveData


@BindingAdapter("soundWaveListData")
fun bindRecyclerView(recyclerView: RecyclerView, data: MutableList<SoundWaveData>) {
    val adapter = recyclerView.adapter as SoundWaveAdapter
    adapter.submitList(data)
}