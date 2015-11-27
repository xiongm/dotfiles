(require 'package)
(push '("marmalade" . "http://marmalade-repo.org/packages/")
      package-archives )
(push '("melpa" . "http://melpa.milkbox.net/packages/")
      package-archives)

;disable automatic package loading
(setq package-enable-at-startup nil)

(defun ensure-package-installed (&rest packages)
  "Assure every package is installed, ask for installation if it’s not.

Return a list of installed packages or nil for every skipped package."
  (mapcar
   (lambda (package)
     (if (package-installed-p package)
         nil
       (if (y-or-n-p (format "Package %s is missing. Install it? " package))
           (package-install package)
         package)))
   packages))

;; Make sure to have downloaded archive description.
(or (file-exists-p package-user-dir)
    (package-refresh-contents))

;; Activate installed packages
(package-initialize)

(ensure-package-installed 'elscreen 
                          'evil
                          'evil-leader
			  'key-chord
			  'smart-mode-line
			  'smart-mode-line-powerline-theme
			  'monokai-theme
			  'auto-complete
                          'helm)

(package-initialize)


(require 'evil-leader)
(global-evil-leader-mode)
(require 'evil)
(evil-mode t)
(require 'dired-x)

;yes/no to y/n 
(fset 'yes-or-no-p 'y-or-n-p)
;treat the file as symlinks
(setq vc-follow-symlinks nil)
;ctrl-hjkl to move between windowsx
(define-key evil-normal-state-map (kbd "C-h") 'evil-window-left)
(define-key evil-normal-state-map (kbd "C-j") 'evil-window-down)
(define-key evil-normal-state-map (kbd "C-k") 'evil-window-up)
(define-key evil-normal-state-map (kbd "C-l") 'evil-window-right)
(define-key evil-normal-state-map (kbd "C-e") 'evil-end-of-line)
(define-key evil-insert-state-map (kbd "C-e") 'evil-end-of-line)
(define-key evil-insert-state-map (kbd "C-a") 'evil-beginning-of-line)
(define-key evil-normal-state-map [escape] 'keyboard-quit)
(define-key evil-visual-state-map [escape] 'keyboard-quit)
;don't move cursor back one position when exiting insert mode
(setq evil-move-cursor-back nil)

(evil-leader/set-leader ",")
;(evil-leader/set-key "q" 'kill-buffer-and-window
(evil-leader/set-key "v" 'split-window-right)
(evil-leader/set-key "s" 'split-window-below)
(evil-leader/set-key "," 'other-window)
(evil-leader/set-key "x" 'helm-M-x)
(evil-leader/set-key "r" 'dired-jump)
(evil-leader/set-key "w" 'save-buffer)

;no tool bar
(tool-bar-mode -1)
(scroll-bar-mode -1)
(setq linum-format "%d ")
(global-linum-mode t)
(global-hl-line-mode t)
(set-face-background 'hl-line "#313537")

;simulate vim's tabs
(load "elscreen" "ElScreen" t)
(setq elscreen-tab-display-control nil)
(setq elscreen-tab-display-kill-screen nil)
(elscreen-start)
(evil-leader/set-key "tn" 'elscreen-create)
(evil-leader/set-key "td" 'elscreen-kill)
(define-key evil-normal-state-map "H" 'elscreen-previous) ;previous tab
(define-key evil-normal-state-map "L" 'elscreen-next) ;next tab

;activate smart mode line
(setq sml/no-confirm-load-theme t)
(setq sml/theme 'light)
(sml/setup)


;auto complete
(ac-config-default)

;press jj quickly to exit insert mode
;requires key-chord
(key-chord-mode 1)
(key-chord-define evil-insert-state-map "jj" 'evil-normal-state)

;bind ENTER w/ autoindent
;same as C-j
(define-key global-map (kbd "RET") 'newline-and-indent)

;set indentwidth for c/cpp/java
;also set indent style to linux
;emacs defaults to gnu, which indents
;braces. we don't want to indent braces
(setq c-default-style "linux"
      c-basic-offset 2)


(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(custom-safe-themes (quote ("196cc00960232cfc7e74f4e95a94a5977cb16fd28ba7282195338f68c84058ec" default)))
 '(inhibit-startup-screen t)
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:family "Monospace" :foundry "unknown" :slant normal :weight normal :height 145 :width normal)))))



(load-theme 'monokai)

