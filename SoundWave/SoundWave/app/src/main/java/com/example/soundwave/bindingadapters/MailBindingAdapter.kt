package com.example.soundwave.bindingadapters

import androidx.databinding.BindingAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.soundwave.adapters.MailAdapter
import com.example.soundwave.datas.MailData


@BindingAdapter("mailListData")
fun bindRecyclerView(recyclerView: RecyclerView, data: MutableList<MailData>) {
    val adapter = recyclerView.adapter as MailAdapter
    adapter.submitList(data)
}