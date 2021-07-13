package com.example.soundwave.fragments

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.activityViewModels
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.soundwave.adapters.MailAdapter
import com.example.soundwave.databinding.FragmentMailBinding
import com.example.soundwave.models.MailViewModel


class MailFragment : Fragment() {

    private var binding: FragmentMailBinding? = null

    private val sharedViewModel: MailViewModel by activityViewModels()

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val fragmentBinding = FragmentMailBinding.inflate(inflater, container, false)
        binding = fragmentBinding
        return fragmentBinding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        binding?.apply {
            lifecycleOwner = this@MailFragment
            viewModel = sharedViewModel
            mailRecyclerView.adapter = MailAdapter()
            mailRecyclerView.layoutManager = LinearLayoutManager(requireContext())
        }
    }
}