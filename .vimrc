let mapleader=";"

filetype on
filetype plugin on

vnoremap <Leader>y "+y
nmap <Leader>p "+p

set incsearch
set ignorecase
set nocompatible
set wildmenu

runtime bundle/pathogen/autoload/pathogen.vim
execute pathogen#infect()

set gcr=a:block-blinkon0
set guioptions-=l
set guioptions-=L
set guioptions-=r
set guioptions-=R
set guioptions-=m
set guioptions-=T

set laststatus=2
set number 
set hlsearch
"set cursorline

syntax enable
syntax on

filetype indent on
set expandtab
set ts=4
set sw=4
