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
			  'smart-mode-line
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

(evil-leader/set-leader ",")
;(evil-leader/set-key "q" 'kill-buffer-and-window)
(evil-leader/set-key "v" 'split-window-right)
(evil-leader/set-key "," 'other-window)
(evil-leader/set-key "x" 'helm-M-x)
(evil-leader/set-key "r" 'dired-jump)
(evil-leader/set-key "w" 'save-buffer)

;no tool bar
(tool-bar-mode -1)

;simulate vim's tabs
(load "elscreen" "ElScreen" t)
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
