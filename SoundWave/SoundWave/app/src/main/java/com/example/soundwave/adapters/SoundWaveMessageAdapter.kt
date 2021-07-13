package com.example.soundwave.adapters

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.soundwave.databinding.SoundWaveMessageItemBinding
import com.example.soundwave.datas.SoundWaveMessageData


// 音波消息的适配器
class SoundWaveMessageAdapter :
    ListAdapter<SoundWaveMessageData, SoundWaveMessageAdapter.SoundWaveMessageViewHolder>(DiffCallback) {

    companion object DiffCallback : DiffUtil.ItemCallback<SoundWaveMessageData>() {
        override fun areItemsTheSame(oldItem: SoundWaveMessageData, newItem: SoundWaveMessageData): Boolean {
            return oldItem.id == newItem.id
        }

        override fun areContentsTheSame(oldItem: SoundWaveMessageData, newItem: SoundWaveMessageData): Boolean {
            return oldItem.content == newItem.content
        }

    }

    class SoundWaveMessageViewHolder(
        private var binding: SoundWaveMessageItemBinding
    ): RecyclerView.ViewHolder(binding.root) {

        fun bind(soundWaveMessageData: SoundWaveMessageData) {
            binding.data = soundWaveMessageData
            binding.executePendingBindings()
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): SoundWaveMessageViewHolder {
        return SoundWaveMessageViewHolder(SoundWaveMessageItemBinding.inflate(LayoutInflater.from(parent.context)))
    }

    override fun onBindViewHolder(holder: SoundWaveMessageViewHolder, position: Int) {
        val item = getItem(position)
        holder.bind(item)
    }
}