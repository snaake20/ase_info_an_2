namespace PAW_S07
{
    partial class Seminar7
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tbData = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tbEur = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tbUsd = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.tbGbp = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tbXau = new System.Windows.Forms.TextBox();
            this.btnParsare = new System.Windows.Forms.Button();
            this.btnGenerare = new System.Windows.Forms.Button();
            this.tvXml = new System.Windows.Forms.TreeView();
            this.cmTv = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.btnTv = new System.Windows.Forms.Button();
            this.exportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cmTv.SuspendLayout();
            this.SuspendLayout();
            // 
            // tbData
            // 
            this.tbData.Location = new System.Drawing.Point(53, 6);
            this.tbData.Name = "tbData";
            this.tbData.Size = new System.Drawing.Size(100, 20);
            this.tbData.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(39, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "DATA:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 35);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(33, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "EUR:";
            // 
            // tbEur
            // 
            this.tbEur.Location = new System.Drawing.Point(53, 32);
            this.tbEur.Name = "tbEur";
            this.tbEur.Size = new System.Drawing.Size(100, 20);
            this.tbEur.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(33, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "USD:";
            // 
            // tbUsd
            // 
            this.tbUsd.Location = new System.Drawing.Point(53, 58);
            this.tbUsd.Name = "tbUsd";
            this.tbUsd.Size = new System.Drawing.Size(100, 20);
            this.tbUsd.TabIndex = 4;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 84);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(32, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "GBP:";
            // 
            // tbGbp
            // 
            this.tbGbp.Location = new System.Drawing.Point(53, 84);
            this.tbGbp.Name = "tbGbp";
            this.tbGbp.Size = new System.Drawing.Size(100, 20);
            this.tbGbp.TabIndex = 6;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 110);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(32, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "XAU:";
            // 
            // tbXau
            // 
            this.tbXau.Location = new System.Drawing.Point(53, 110);
            this.tbXau.Name = "tbXau";
            this.tbXau.Size = new System.Drawing.Size(100, 20);
            this.tbXau.TabIndex = 8;
            // 
            // btnParsare
            // 
            this.btnParsare.Location = new System.Drawing.Point(12, 415);
            this.btnParsare.Name = "btnParsare";
            this.btnParsare.Size = new System.Drawing.Size(75, 23);
            this.btnParsare.TabIndex = 10;
            this.btnParsare.Text = "Parsare XML";
            this.btnParsare.UseVisualStyleBackColor = true;
            this.btnParsare.Click += new System.EventHandler(this.btnParsare_Click);
            // 
            // btnGenerare
            // 
            this.btnGenerare.Location = new System.Drawing.Point(93, 415);
            this.btnGenerare.Name = "btnGenerare";
            this.btnGenerare.Size = new System.Drawing.Size(75, 23);
            this.btnGenerare.TabIndex = 11;
            this.btnGenerare.Text = "Generare XML";
            this.btnGenerare.UseVisualStyleBackColor = true;
            this.btnGenerare.Click += new System.EventHandler(this.btnGenerare_Click);
            // 
            // tvXml
            // 
            this.tvXml.ContextMenuStrip = this.cmTv;
            this.tvXml.Location = new System.Drawing.Point(471, 9);
            this.tvXml.Name = "tvXml";
            this.tvXml.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.tvXml.Size = new System.Drawing.Size(182, 121);
            this.tvXml.TabIndex = 12;
            // 
            // cmTv
            // 
            this.cmTv.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exportToolStripMenuItem});
            this.cmTv.Name = "contextMenuStrip1";
            this.cmTv.Size = new System.Drawing.Size(181, 48);
            // 
            // btnTv
            // 
            this.btnTv.Location = new System.Drawing.Point(174, 415);
            this.btnTv.Name = "btnTv";
            this.btnTv.Size = new System.Drawing.Size(75, 23);
            this.btnTv.TabIndex = 13;
            this.btnTv.Text = "Tree View";
            this.btnTv.UseVisualStyleBackColor = true;
            this.btnTv.Click += new System.EventHandler(this.btnTv_Click);
            // 
            // exportToolStripMenuItem
            // 
            this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
            this.exportToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.exportToolStripMenuItem.Text = "Export";
            this.exportToolStripMenuItem.Click += new System.EventHandler(this.exportToolStripMenuItem_Click);
            // 
            // Seminar7
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btnTv);
            this.Controls.Add(this.tvXml);
            this.Controls.Add(this.btnGenerare);
            this.Controls.Add(this.btnParsare);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.tbXau);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.tbGbp);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tbUsd);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbEur);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbData);
            this.Name = "Seminar7";
            this.Text = "Seminar7";
            this.cmTv.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbData;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbEur;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbUsd;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tbGbp;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox tbXau;
        private System.Windows.Forms.Button btnParsare;
        private System.Windows.Forms.Button btnGenerare;
        private System.Windows.Forms.TreeView tvXml;
        private System.Windows.Forms.Button btnTv;
        private System.Windows.Forms.ContextMenuStrip cmTv;
        private System.Windows.Forms.ToolStripMenuItem exportToolStripMenuItem;
    }
}

