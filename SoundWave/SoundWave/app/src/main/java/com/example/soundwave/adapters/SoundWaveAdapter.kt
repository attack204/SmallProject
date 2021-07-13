package com.example.soundwave.adapters

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.soundwave.databinding.SoundWaveItemBinding
import com.example.soundwave.datas.SoundWaveData


class SoundWaveAdapter :  
    ListAdapter<SoundWaveData, SoundWaveAdapter.SoundWaveViewHolder>(DiffCallback) {

    companion object DiffCallback : DiffUtil.ItemCallback<SoundWaveData>() {
        override fun areItemsTheSame(oldItem: SoundWaveData, newItem: SoundWaveData): Boolean {
            return oldItem.id == newItem.id
        }

        override fun areContentsTheSame(oldItem: SoundWaveData, newItem: SoundWaveData): Boolean {
            return oldItem.soundWaveName == newItem.soundWaveName
        }

    }

    class SoundWaveViewHolder(
        private var binding: SoundWaveItemBinding
    ): RecyclerView.ViewHolder(binding.root) {

        fun bind(soundWaveData: SoundWaveData) {
            binding.data = soundWaveData
            binding.executePendingBindings()
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): SoundWaveViewHolder {
        return SoundWaveViewHolder(SoundWaveItemBinding.inflate(LayoutInflater.from(parent.context)))
    }

    override fun onBindViewHolder(holder: SoundWaveViewHolder, position: Int) {
        val item = getItem(position)
        holder.bind(item)
    }

//    override fun onBindViewHolder(holder: SoundWaveViewHolder, position: Int) {
//        val item = soundWaveList[position]
//        holder.textView.text = item
//
//        holder.textView.setOnClickListener {
//            val action = SoundWaveFragmentDirections.actionSoundWaveFragmentToTrackFragment(
//                soundWaveId = holder.textView.text.toString()
//            )
//            holder.view.findNavController().navigate(action)
//        }
//    }
}