package com.example.soundwave.adapters

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.soundwave.databinding.MailItemBinding
import com.example.soundwave.datas.MailData


// 音讯适配器
class MailAdapter :
    ListAdapter<MailData, MailAdapter.MailViewHolder>(DiffCallback) {

    companion object DiffCallback : DiffUtil.ItemCallback<MailData>() {
        override fun areItemsTheSame(oldItem: MailData, newItem: MailData): Boolean {
            return oldItem.id == newItem.id
        }

        override fun areContentsTheSame(oldItem: MailData, newItem: MailData): Boolean {
            return oldItem.content == newItem.content
        }

    }

    class MailViewHolder(
        private var binding: MailItemBinding
    ): RecyclerView.ViewHolder(binding.root) {

        fun bind(mailData: MailData) {
            binding.data = mailData
            binding.executePendingBindings()
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MailViewHolder {
        return MailAdapter.MailViewHolder(
            MailItemBinding.inflate(
                LayoutInflater.from(
                    parent.context
                )
            )
        )
    }

    override fun onBindViewHolder(holder: MailViewHolder, position: Int) {
        val item = getItem(position)
        holder.bind(item)
    }
}